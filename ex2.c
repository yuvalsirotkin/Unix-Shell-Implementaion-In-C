//
// Created by yuval on 4/25/20.
//
//
// Created by yuval on 4/25/20.
//

#include <wchar.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>


struct process
{
    char* command;
    pid_t pid;
    int done; // 0 = false, 1= true;
};

void doCommand (char* arr[], int len, int background, int* numberOfProcess, struct process* processArray) ;
void exitCommand (char* arr[]);
void execCommand (char* arr[]) ;
void cdCommand (char* arr[], int len);
void jobsCommand (char* arr[], int* numberOfProcess, struct process* processArray);
void historyCommand (char* arr[], int* numberOfProcess, struct process* processArray);
void checkIfBackground (char* inst, char** arr, int len, int* numberOfProcess, struct process* processArray) ;
void update(int numberOfProcess, struct process* processArray);
void forkOrBuiltIn(char* instInString, char* arr[], int len, int* numberOfProcess, struct process* processArray);



static int stop = 0; // exit = false
static char* homeDir;
char prevPath[1000];
int main () {
    int numberOfProcess = 0;
    struct process processArray[100];


    homeDir = getenv("HOME");
    if (homeDir == NULL) {
        fprintf(stderr, "Error in system call");;
    }
    if (getcwd(prevPath, sizeof(prevPath)) == NULL) {
        fprintf(stderr, "Error in system call");;
    }
    while (!stop) {
        char inst[100];
        int i = 0;
        // scan the instructions from the user
        char* str = (char *)malloc(100 * sizeof(char));
        if (str == NULL) {
            fprintf(stderr, "Error in system call");
        }
        printf("> ");
        fgets(str,100,stdin);
        strcpy(inst, str);

        //remove the "\n" from the string
        str = strtok(str, "\n");
        char *word = strtok (inst, " ");
        char *array[100];
        array[i] = word;
        int lenUntilNewWord = (int) strlen(word) + 1;
        // if the last word is not the last argument in the input
        while (word[strlen(word) - 1] != '\n')
        {
            word = strtok (inst + lenUntilNewWord, " ");
            i = i+1;
            array[i] = word;
            lenUntilNewWord += (int) strlen(word) + 1;
        }
        // removing the \n from the last cell
        array[i] = strtok (array[i], "\n");
        i++;
        array[i] = NULL;
        i++;

        forkOrBuiltIn(str,array,i, &numberOfProcess, processArray);



        // i is with the NULL cell - array[i] == NULL
        //checkIfBackground(str, array, i, &numberOfProcess, processArray);
        // update the process's array
        update(numberOfProcess, processArray);
    }
    return 0;
}


void forkOrBuiltIn(char* instInString , char* arr[], int len,  int* numberOfProcess, struct process* processArray) {
    if (strcmp(arr[0], "exit") == 0 ) {
        struct process newP = {instInString, getpid(), 0};
        processArray[*numberOfProcess] = newP;
        (*numberOfProcess)++;
        exitCommand(arr);
    }
    else if (strcmp(arr[0], "cd") == 0 ) {
        struct process newP = {instInString, getpid(), 0};
        processArray[*numberOfProcess] = newP;
        (*numberOfProcess)++;
        cdCommand(arr, len);
    }
    else if (strcmp(arr[0], "jobs") == 0 ) {
        struct process newP = {instInString, getpid(), 0};
        processArray[*numberOfProcess] = newP;
        (*numberOfProcess)++;
        jobsCommand(arr, numberOfProcess, processArray);
    }
    else if (strcmp(arr[0], "history") == 0 ) {
        struct process newP = {instInString, getpid(), 0};
        processArray[*numberOfProcess] = newP;
        (*numberOfProcess)++;
        historyCommand(arr, numberOfProcess, processArray);
    }
    else {
        checkIfBackground(instInString, arr, len, numberOfProcess, processArray);
        //execCommand(arr);
    }

}


//void getCurrDir(char* path, char* substring) {
//
//    int begin = 0;
//    for (int i = 0 ; i < 1000 ; i++) {
//        if (path[i] == '/') {
//            begin = i;
//        } else if (path[i] == '\0') {
//            break;
//        }
//    }
//    printf("begin is %d\n", begin);
//    for (int i =0  ; i <= begin ; i++) {
//        substring[i] = path[i];
//    }
//
//}

void copyStrings(char* dest, char* source) {
    // nullify the array
    for (int i = 0 ; i < 1000 ; i++) {
        dest[i] = '\0';
    }
    for (int i =0  ; i < 1000; i++) {
        dest[i] = source[i];
    }
}

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    if (result == NULL) {
        fprintf(stderr, "Error in system call");
    }
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void cdCommand (char* arr[], int len){
    // because of the null in the end of the array- if len == 2 this is just cd without argument
    printf("%d\n", getpid());
    if (len > 3){
        fprintf(stderr, "Error: Too many arguments");
    } else {
        if (len == 2 || strcmp(arr[1], "~") == 0 ) {
            if (getcwd(prevPath, sizeof(prevPath)) == NULL) {
                fprintf(stderr, "Error in system call");
            }

            chdir(homeDir);
        }
        else if (arr[1][0]== '~') {
            if (getcwd(prevPath, sizeof(prevPath)) == NULL) {
                fprintf(stderr, "Error in system call");
            }
            int idxToDel = 0;
            memmove(&arr[1][idxToDel], &arr[1][idxToDel + 1], strlen(arr[1]) - idxToDel);
            char* newPath = concat(homeDir, arr[1]);
            chdir(newPath);
        }
        else if (strcmp(arr[1], "-") == 0 ) {
            char temp[1000];
            if (getcwd(temp, sizeof(temp)) == NULL) {
                fprintf(stderr, "Error in system call");;
            }
            chdir(prevPath);
            copyStrings (prevPath,temp);
            printf ("prev is %s\n" , prevPath);
        }
        else  {
            // temp contain the prev path
            char temp[1000];
            copyStrings (temp, prevPath);
            if (getcwd(prevPath, sizeof(prevPath)) == NULL) {
                fprintf(stderr, "Error in system call");
            }
                // prev contain the curr path
            else{
                if ((chdir(arr[1]) == -1) ) {
                    fprintf(stderr, "Error: No such file or directory");
                    // if there is an error- prev should contain temp;
                    copyStrings(prevPath, temp);
                }
            }
            printf ("prev is %s\n" , prevPath);


        }
    }
}


void exitCommand (char* arr[]) {
    printf("%d\n", getpid());
    stop = 1;
}

void checkIfBackground (char* instInString, char* arr[], int len, int* numberOfProcess, struct process* processArray) {
    pid_t val;
    int status;
    int background = (strcmp(arr[len-2], "&") == 0); // 1 if background
    char* arrayToExecv[len -1];
    if (background) { // remove the & from the array
        for (int i = 0; i < len -2; i++) {
            arrayToExecv[i] = arr [i];
        }
        arrayToExecv[len-2] = NULL;

    }
    *numberOfProcess = (*numberOfProcess) + 1;
    val = fork();
    if (val == -1) {
        fprintf(stderr, "Error in system call");
    }
    if (val > 1) { // this is the father
        // insert to the process array before the fork!
        ///////////////check what to do if this is invalid command//////////
        if (!background) {
            struct process newP = {instInString, val, 0};
            processArray[*numberOfProcess -1] = newP;
        } else {
            struct process newP = {arrayToExecv, val, 0};
            processArray[*numberOfProcess -1] = newP;
        }
        if (!background) { // the father need to wait for his son (specific son)
            waitpid(val, &status, 0);
        }
    }

    if (val == 0) { // this is the son
        printf("%d\n", getpid());
        if (background) {
            execCommand(arrayToExecv);
        } else {
            execCommand(arr);
        }
    }
    //else- this is foreground and this is the father -continue
    // after the father end- continue
}

int lenIfMarks(char* string) {
    int i = 0;
    if (string[0] == '"' && i < 1000) {
        while (string[i] != '\0') {
            i++;
        }
    }
    if (string[i] == '\0') {
        return i;
    }
    return -1;
}

void removeMarks (char* string, char withoutMarks[], int len) {
    for (int j = 0 ; j < len - 2 ; j++) {
        withoutMarks[j] = string[j+1];
    }
    withoutMarks[len - 2] = '\0';
}

void execCommand(char* arr[]) {

    int ret_code;
    if (strcmp(arr[0] , "echo") == 0) {
        int len = lenIfMarks(arr[1]);
        if (len == -1) { // there is no ""
            ret_code = execlp("echo", "echo" ,arr[1], NULL);
        } else {
            char withoutMarks[len-2];
            removeMarks(arr[1], withoutMarks, len);
            ret_code = execlp("echo", "echo" ,withoutMarks, NULL);
        }
    } else {
        ret_code= execvp((char* const) arr[0], (char *const *) arr);
    }

    // if there was no error this code will not be executed
    if (ret_code == -1)
    {
        fprintf(stderr, "Error in system call");
    }

}


// update the process's array
void update(int numberOfProcess, struct process* processArray){
    for (int i = 0; i < numberOfProcess ; i++) {
        int status;
        //check if the process is still alive
        int isAlive = waitpid(processArray[i].pid, &status, WNOHANG);
        if (isAlive != 0) {
            processArray[i].done = 1;
        }
//        printf("test: procces number: %d, pid: %d, command: %s done: %d\n", i, processArray[i].pid,
//               processArray[i].command, processArray[i].done);
    }
}


void historyCommand (char** arr, int* numberOfProcess, struct process* processArray) {
    for (int i = 0; i < *numberOfProcess; i++) {
        if (processArray[i].done) {
            printf("%d %s DONE\n", processArray[i].pid, processArray[i].command);
        } else {
            printf("%d %s RUNING\n", processArray[i].pid, processArray[i].command);
        }
    }
}

void jobsCommand (char* arr[], int* numberOfProcess, struct process* processArray){
    for (int i = 0; i < *numberOfProcess; i++) {
        if (!processArray[i].done && strcmp(processArray[i].command, "jobs") != 0) {
            printf("%d %s\n", processArray[i].pid, processArray[i].command);
        }
    }
}





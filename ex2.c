//
// Created by yuval on 4/25/20.
//


#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <ctype.h>


struct process
{
    char* command;
    pid_t pid;
    int done; // 0 = false, 1= true;
};

void exitCommand (char* arr[]);
void execCommand (char* arr[]) ;
void cdCommand (char* arr[], int len);
void jobsCommand (const int* numberOfProcess, struct process* processArray);
void historyCommand (char* arr[], const int* numberOfProcess, struct process* processArray);
void checkIfBackground (char* inst, char** arr, int len, int* numberOfProcess, struct process* processArray) ;
void update(int numberOfProcess, struct process* processArray);
void forkOrBuiltIn(char* instInString, char* arr[], int len, int* numberOfProcess, struct process* processArray);
char* removeWhiteSpace(char *str);



static int stop = 0; // exit = false
static char* homeDir;
char prevPath[1000];

char *trimwhitespace(char *string)
{
    char *str = strdup(string);
    char *end;

    // Trim leading space
    while(isspace((unsigned char)*str)) str++;


    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator character
    end[1] = '\0';

    return str;
}

int main () {
    int numberOfProcess = 0;
    struct process processArray[100];

    homeDir = getenv("HOME");
    if (homeDir == NULL) {
        fprintf(stderr, "Error in system call\n");
    }
    if (getcwd(prevPath, sizeof(prevPath)) == NULL) {
        fprintf(stderr, "Error in system call\n");
    }
    while (!stop) {
        char inst[100];
        // scan the instructions from the user
        char* str1 = (char *)malloc(100 * sizeof(char));
        if (str1 == NULL) {
            fprintf(stderr, "Error in system call\n");
        }
        printf("> ");
        fgets(str1,100,stdin);
        //while(isspace((unsigned char)* str1)) str1++;
        char* str =trimwhitespace(str1);
        strcpy(inst, str);
        //remove the "\n" from the string
        //str = strtok(str, "\n");
        char *word = strtok (inst, " ");
        char *array[100];
        int size = 0;
        while (word != NULL){
            array[size] = word;
            word = strtok (NULL, " ");
            size++;
        }
        //removing the \n from the last cell
        array[size-1] = strtok (array[size-1], "\n");
        array[size] = NULL;
        size ++;
        ////// to do - in note echo "   y"
        printf("main %s\n", array[1]);
        forkOrBuiltIn(str,array,size, &numberOfProcess, processArray);
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
        jobsCommand(numberOfProcess, processArray);
    }
    else if (strcmp(arr[0], "history") == 0 ) {
        struct process newP = {instInString, getpid(), 0};
        processArray[*numberOfProcess] = newP;
        (*numberOfProcess)++;
        historyCommand(arr, numberOfProcess, processArray);
    }
    else {
        checkIfBackground(instInString, arr, len, numberOfProcess, processArray);
    }

}


void copyStrings(char* dest,const char* source) {
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
        fprintf(stderr, "Error in system call\n");
    }
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void deleteChar(char* string, int idxToDel) {
    memmove(&string[idxToDel], &string[idxToDel + 1], strlen(string) - idxToDel);

}

void cdCommand (char* arr[], int len){
    // because of the null in the end of the array- if len == 2 this is just cd without argument
    printf("%d\n", getpid());
    if (len > 3){
        fprintf(stderr, "Error: Too many arguments\n");
    } else {
        if (len == 2 || strcmp(arr[1], "~") == 0 ) {
            if (getcwd(prevPath, sizeof(prevPath)) == NULL) {
                fprintf(stderr, "Error in system call\n");
            }

            chdir(homeDir);
        }
        else if (arr[1][0]== '~') {
            if (getcwd(prevPath, sizeof(prevPath)) == NULL) {
                fprintf(stderr, "Error in system call\n");
            }
            deleteChar(arr[1], 0);
            char* newPath = concat(homeDir, arr[1]);
            chdir(newPath);
        }
        else if (strcmp(arr[1], "-") == 0 ) {
            char temp[1000];
            if (getcwd(temp, sizeof(temp)) == NULL) {
                fprintf(stderr, "Error in system call\n");
            }
            chdir(prevPath);
            copyStrings (prevPath,temp);
        }
        else  {
            // temp contain the prev path
            char temp[1000];
            copyStrings (temp, prevPath);
            if (getcwd(prevPath, sizeof(prevPath)) == NULL) {
                fprintf(stderr, "Error in system call\n");
            }
                // prev contain the curr path
            else{
                if ((chdir(arr[1]) == -1) ) {
                    fprintf(stderr, "Error: No such file or directory\n");
                    // if there is an error- prev should contain temp;
                    copyStrings(prevPath, temp);
                }
            }
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
        fprintf(stderr, "Error in system call\n");
    }
    if (val > 1) { // this is the father
        // insert to the process array before the fork!
        if (!background) {
            struct process newP = {instInString, val, 0};
            processArray[*numberOfProcess -1] = newP;
            waitpid(val, &status, 0);
        } else {
            deleteChar(instInString, (int) strlen(instInString)-1);
            deleteChar(instInString, (int) strlen(instInString)-1);
            struct process newP = {instInString, val, 0};
            processArray[*numberOfProcess -1] = newP;
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

int checkIfMarks(char* string) {
    if (string[0] == '\"' && string[strlen(string) -1] == '\"') {
        return 1;
    } else {
        return 0;
    }
}

void removeMarks (char* string, char withoutMarks[], int len) {
    printf("without %d\n", len);
    for (int j = 0 ; j < len - 2 ; j++) {
        withoutMarks[j] = string[j+1];
    }
    withoutMarks[len - 2] = '\0';
    printf("without %s\n", withoutMarks);
}

void execCommand(char* arr[]) {
    int ret_code;
    if (strcmp(arr[0] , "echo") == 0) {
        int haveMarks = checkIfMarks(arr[1]);
        if (!haveMarks) { // there is no ""
            ret_code = execlp("echo", "echo" ,arr[1], NULL);
        } else {
            printf("arr1 %s\n", arr[1]);
            char withoutMarks[(int) strlen(arr[1]) - 2];
            removeMarks(arr[1], withoutMarks, (int) strlen(arr[1]));
            printf("without %s\n", withoutMarks);
            ret_code = execlp("echo", "echo" ,withoutMarks, NULL);
        }
    } else {
        ret_code= execvp((char* const) arr[0], (char *const *) arr);
    }

    // if there was no error this code will not be executed
    if (ret_code == -1)
    {
        fprintf(stderr, "Error in system call\n");
        exit(1);
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
    }
}


void historyCommand (char** arr, const int* numberOfProcess, struct process* processArray) {
    for (int i = 0; i < *numberOfProcess; i++) {
        if (processArray[i].done) {
            printf("%d %s DONE\n", processArray[i].pid, processArray[i].command);
        } else {
            printf("%d %s RUNNING\n", processArray[i].pid, processArray[i].command);
        }
    }
}

void jobsCommand (const int* numberOfProcess, struct process* processArray){
    for (int i = 0; i < *numberOfProcess; i++) {
        if (!processArray[i].done && strcmp(processArray[i].command, "jobs") != 0) {
            printf("%d %s\n", processArray[i].pid, processArray[i].command);
        }
    }
}
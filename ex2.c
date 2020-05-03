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

#define MAX_INPUT_SIZE 1000
struct process
{
    char* command;
    pid_t pid;
    int done; // 0 = false, 1= true;
};

void exitCommand ();
void execCommand (char* arr[MAX_INPUT_SIZE], int len) ;
void cdCommand (char* arr[MAX_INPUT_SIZE], int len);
void jobsCommand (const int* numberOfProcess, struct process* processArray);
void historyCommand (char* arr[MAX_INPUT_SIZE], const int* numberOfProcess, struct process* processArray);
void checkIfBackground (char* inst, char* arr[MAX_INPUT_SIZE], int len, int* numberOfProcess, struct process* processArray) ;
void update(int numberOfProcess, struct process* processArray);
void forkOrBuiltIn(char* instInString, char* arr[MAX_INPUT_SIZE], int len, int* numberOfProcess, struct process* processArray);
void deleteArrays(char* arr[MAX_INPUT_SIZE], int len);


static int stop = 0; // exit = false
static char* homeDir;
char prevPath[1000];

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
        int i,k,sum=0, j=0;
        // scan the instructions from the user
        // need to malloc in order to have different strings in the process array
        char* input = (char *)malloc(100 * sizeof(char));
        if (input == NULL) {
            fprintf(stderr, "Error in system call\n");
        }
        printf("> ");
        // nullify the tokens
        char tokens[MAX_INPUT_SIZE][MAX_INPUT_SIZE] = {0};
        fgets(input,100,stdin);
        // remove the \n from the string
        input[strlen(input)-1] = 0;
        // check how many quotation marks there are in the input
        for (i = 0; i < strlen(input); i++) {
            if (input[i] == '\"') {
                sum++;
            }
        }
        if (sum % 2 != 0) {
            fprintf(stderr, "Error odd number of quotation marks\n");
            continue;
        }

        // delete spaces from beginning
        for (i = 0; i < strlen(input); i++) {
            if (input[i] != ' ') {
                break;
            }
        }

        for (j = 0, k = 0; i < strlen(input); i++) {
            // first quotation mark
            if (input[i] == '\"') {
                i++;
                // concatenate the words between the quotation marks
                while (input[i] != '\"'){
                    tokens[j][k]=input[i];
                    i++;
                    k++;
                }

                // go to next word
            } else if (input[i] == ' ') {
                k=0;
                j++;
                for (; i < strlen(input); i++) {
                    if (input[i] != ' ')break;
                }
                i--;
                // continue concatenating the word
            } else {
                tokens[j][k]=input[i];
                k++;
            }
        }
        char *args[j+2];
        for (i = 0; i < MAX_INPUT_SIZE - 1; i++) {
            if (tokens[i][0] != 0) {
                args[i] = tokens[i];
            } else {
                break;
            }
        }
        args[i-1] = strtok (args[i-1], "\n");
        args[i] = NULL;

        forkOrBuiltIn(input,args,i+1, &numberOfProcess, processArray);
        // update the process's array - check what done
        update(numberOfProcess, processArray);
        deleteArrays(args, i+1);
    }
    return 0;
}

void deleteArrays(char* arr[MAX_INPUT_SIZE], int len) {
    for (int i=0; i< len ; i++) {
        arr[i]= 0;
    }
}


void forkOrBuiltIn(char* instInString , char* arr[MAX_INPUT_SIZE], int len,  int* numberOfProcess, struct process* processArray) {
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

//concat 2 strings wit malloc
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

//delete char from specific index
void deleteChar(char* string, int idxToDel) {
    memmove(&string[idxToDel], &string[idxToDel + 1], strlen(string) - idxToDel);

}

void cdCommand (char* arr[MAX_INPUT_SIZE], int len){
    // because of the null in the end of the array- if len == 2 this is just cd without argument
    printf("%d\n", getpid());
    if (len > 3){
        fprintf(stderr, "Error: Too many arguments\n");
    } else {
        // cd without arguments or ~ - go to home
        if (len == 2 || strcmp(arr[1], "~") == 0 ) {
            if (getcwd(prevPath, sizeof(prevPath)) == NULL) {
                fprintf(stderr, "Error in system call\n");
            }
            chdir(homeDir);
        }
            // ~/path
        else if (arr[1][0]== '~') {
            if (getcwd(prevPath, sizeof(prevPath)) == NULL) {
                fprintf(stderr, "Error in system call\n");
            }
            deleteChar(arr[1], 0);
            char* newPath = concat(homeDir, arr[1]);
            chdir(newPath);
        }
            // go to previous
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

//exit - stop while loop in main
void exitCommand () {
    printf("%d\n", getpid());
    stop = 1;
}


void checkIfBackground (char* instInString, char* arr[MAX_INPUT_SIZE], int len, int* numberOfProcess,
                        struct process* processArray) {
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
            execCommand(arrayToExecv, len);
        } else {
            execCommand(arr, len);
        }
    }
    //else- this is foreground and this is the father -continue
    // after the father end- continue
}


void execCommand(char* arr[MAX_INPUT_SIZE], int len) {
    int ret_code;
    if (strcmp(arr[0] , "echo") == 0) {
        ret_code = execvp("echo", arr);
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


void historyCommand (char* arr[MAX_INPUT_SIZE], const int* numberOfProcess, struct process* processArray) {
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
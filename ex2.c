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

//void doCommand (char** arr, int len, int background);
//void exitCommand (char** arr, int len);
//void execCommand (char** arr, int len);
//void cdCommand (char** arr, int len);
//void jobsCommand (char** arr, int len);
//void historyCommand (char** arr, int len);
//void checkIfBackground (char** arr, int len);
//void update();

struct process
{
    char** command;
    int pid;
    int done; // 0 = false, 1= true;
};

void doCommand (char** arr, int len, int background) ;
void exitCommand (char** arr, int len);
void execCommand (char** arr, int len) ;
void cdCommand (char** arr, int len);
void jobsCommand (char** arr, int len);
void historyCommand (char** arr, int len);
void checkIfBackground (char** arr, int len, int* numberOfProcess, struct process*** processArray) ;
void update(int numberOfProcess, struct process*** processArray);



void printError() {
    printf("error!!");
}


int main () {
    int exit = 0; // exit = false
    int numberOfProcess = 0;
    struct process processArray[100];

    char* a[100] = {"ab", "cd"};
    struct process newP = {a, 123, 0};
    printf("begin %s", *newP.command);


    while (!exit) {
        char temp;
        char inst[100];
        int i = 0;
        // scan the instructions from the user
        fgets(inst,100,stdin);
        //scanf("%[^\n]", inst);
        char *word = strtok (inst, " ");
        char *array[100];
        array[i] = word;
        int lenUntilNewWord = strlen(word) + 1;
        // if the last word is not the last argument in the input
        while (word[strlen(word) - 1] != '\n')
        {
            word = strtok (inst + lenUntilNewWord, " ");
            i = i+1;
            array[i] = word;
            lenUntilNewWord += strlen(word) + 1;
        }

        // removing the \n from the last cell
        array[i] = strtok (array[i], "\n");
        i++;
        array[i] = NULL;
        i++;

        // i is with the NULL cell - array[i] == NULL
        checkIfBackground(array, i, &numberOfProcess, (struct process ***) processArray);
        printf("before up\n");
        update(numberOfProcess, (struct process ***) processArray);
    }
    return 0;
}

void update(int numberOfProcess, struct process*** processArray){
    printf ("%d\n", numberOfProcess);
    printf ("add is %d\n", processArray);
    printf("command is %s\n", *(*processArray[0])->command);
    for (int i = 0; i < numberOfProcess ; i++) {
        printf("test print: %s\n", *(*processArray[numberOfProcess])->command);
        int status;
        //check if the process is still alive
        if (waitpid((*processArray[i])->pid, &status, WNOHANG) != 0) {
            (*processArray[i])->done = 1;
        }
    }
}

void checkIfBackground (char* arr[], int len, int* numberOfProcess, struct process*** processArray) {
    // insert to the process array before the fork!
    ///////////////check what to do if this is invalid command//////////
    struct process newP = {arr, getpid(), 0};
    printf("command iss %s, %d, %d\n", *newP.command, newP.pid, newP.done);
    printf("%d", *numberOfProcess);
    (**processArray)[(*numberOfProcess)] = newP;
    printf("here");
    printf("command is %s\n", *(*processArray[0])->command);
    printf ("add is %d\n", processArray);
    *numberOfProcess = (*numberOfProcess) + 1;

    pid_t val;
    int status;
    int waited;
    int background = (strcmp(arr[len-2], "&") == 0); // 1 if background
    val = fork();
    if (val == -1) {
        printError();
    }
    if (!background && val > 0) { // the father need to wait for his son (specific son)
        printf("test: father waiting\n");
        waited = waitpid(val, &status, 0);
        printf("test: father stop waiting\n");
    }
        // for debug:
    else if (val > 0) {
        printf("test: father doesnt need to wait\n");
    }
    if (val == 0) { // this is the son
        printf("%d\n", getpid());
        printf("should be add %d\n", numberOfProcess);
        doCommand(arr, len, background);
    }
    //else- this is foreground and this is the father -continue
    // after the father end- continue
    printf("end of check");
}





void doCommand (char** arr, int len, int background) {
    if (background) {
        printf("back\n");
        char* arrayToExecv[len -1];
        for (int i = 0; i < len -1; i++) {
            arrayToExecv[i] = arr [i];
        }
        arrayToExecv[len-2] = NULL;
        if (strcmp(arr[0], "exit") == 0 ) {
            exitCommand(arrayToExecv, len -1);
        }
        else if (strcmp(arr[0], "cd") == 0 ) {
            cdCommand(arrayToExecv, len-1);
        }
        else if (strcmp(arr[0], "jobs") == 0 ) {
            jobsCommand(arrayToExecv, len-1);
        }
        else if (strcmp(arr[0], "history") == 0 ) {
            historyCommand(arrayToExecv, len-1);
        } else {
            execCommand(arrayToExecv, len-1);
        }
    }
    else {
        printf("fore\n");
        char* arrayToExecv[len];
        for (int i = 0; i < len; i++) {
            arrayToExecv[i] = arr [i];
        }
        if (strcmp(arr[0], "exit") == 0 ) {
            exitCommand(arrayToExecv, len);
        }
        else if (strcmp(arr[0], "cd") == 0 ) {
            cdCommand(arrayToExecv, len);
        }
        else if (strcmp(arr[0], "jobs") == 0 ) {
            jobsCommand(arrayToExecv, len);
        }
        else if (strcmp(arr[0], "history") == 0 ) {
            historyCommand(arrayToExecv, len);
        } else {
            execCommand(arrayToExecv, len);
        }
    }

}


void execCommand(char* arr[], int len) {
    for (int i = 0 ; i < len ; i++) {
        printf("%d %s", i, arr[i]);
    }

    int ret_code= execvp((char* const) arr[0], (char *const *) arr);

    // if there was no error this code will not be executed
    if (ret_code == -1)
    {
        printError();
    }

}


void exitCommand (char** arr, int len){}
void cdCommand (char** arr, int len){}

void jobsCommand (char** arr, int len){
//    struct process newP = {arr, getpid(), 0};
//    processArray[numberOfProcess] = &newP;
//    numberOfProcess++;
//    for (int i = 0; i <= numberOfProcess; i++) {
//        if (!processArray[i]->done) {
//            printf("%d %s\n", processArray[i]->pid, *processArray[i]->command);
//        }
//    }
}


void historyCommand (char** arr, int len){
//    struct process newP = {arr, getpid(), 0};
//    processArray[numberOfProcess] = &newP;
//    numberOfProcess++;
//    printf("%d", numberOfProcess);
//    for (int i = 0; i < numberOfProcess; i++) {
//        if (processArray[i]->done){
//            printf("%d %s DONE\n" ,processArray[i]->pid, *processArray[i]->command);
//        } else {
//            printf("%d %s RUNING\n" ,processArray[i]->pid ,*processArray[i]->command);
//        }
//    }
//    printf("test end his\n");
}

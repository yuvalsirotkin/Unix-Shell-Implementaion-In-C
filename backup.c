////
//// Created by yuval on 4/25/20.
////
////
//// Created by yuval on 4/25/20.
////
//
//#include <wchar.h>
//#include <string.h>
//#include <stdio.h>
//#include <fcntl.h>
//#include <unistd.h>
//#include <wait.h>
//#include <stdlib.h>
//
//struct process
//{
//    char* command;
//    pid_t pid;
//    int done; // 0 = false, 1= true;
//};
//
//void doCommand (char* arr[], int len, int background, int* numberOfProcess, struct process* processArray) ;
//void exitCommand (char* arr[], int len);
//void execCommand (char* arr[], int len) ;
//void cdCommand (char* arr[], int len);
//void jobsCommand (char* arr[], int* numberOfProcess, struct process* processArray);
//void historyCommand (char* arr[], int* numberOfProcess, struct process* processArray);
//void checkIfBackground (char* inst, char** arr, int len, int* numberOfProcess, struct process* processArray) ;
//void update(int numberOfProcess, struct process* processArray);
//
//
//
//void printError() {
//    printf("error!!\n");
//}
//
//
//int main () {
//    int exit = 0; // exit = false
//    int numberOfProcess = 0;
//    struct process processArray[100];
//
//    while (!exit) {
//        char inst[100];
//        int i = 0;
//        // scan the instructions from the user
//        char* str = (char *)malloc(100 * sizeof(char));
//        fgets(str,100,stdin);
//        strcpy(inst, str);
//
//        //remove the "\n" from the string
//        str = strtok(str, "\n");
//        char *word = strtok (inst, " ");
//        char *array[100];
//        array[i] = word;
//        int lenUntilNewWord = (int) strlen(word) + 1;
//        // if the last word is not the last argument in the input
//        while (word[strlen(word) - 1] != '\n')
//        {
//            word = strtok (inst + lenUntilNewWord, " ");
//            i = i+1;
//            array[i] = word;
//            lenUntilNewWord += (int) strlen(word) + 1;
//        }
//        // removing the \n from the last cell
//        array[i] = strtok (array[i], "\n");
//        i++;
//        array[i] = NULL;
//        i++;
//
//        // i is with the NULL cell - array[i] == NULL
//        checkIfBackground(str, array, i, &numberOfProcess, processArray);
//        // update the process's array
//        update(numberOfProcess, processArray);
//    }
//    return 0;
//}
//
//// update the process's array
//void update(int numberOfProcess, struct process* processArray){
//    for (int i = 0; i < numberOfProcess ; i++) {
//        printf("test: procces number: %d, pid: %d, command: %s done: %d\n", i, processArray[i].pid,
//               processArray[i].command, processArray[i].done);
//        int status;
//        //check if the process is still alive
//        int isAlive = waitpid(processArray[i].pid, &status, WNOHANG);
//        if (isAlive > 0) {
//            processArray[i].done = 1;
//        } else if (isAlive == -1) {
//            printf("there is a problem with the waitpid\n", processArray[i].pid);
//            printError();
//        }
//    }
//}
//
//void cdCommand (char** arr, int len){
//
//}
//
//void historyCommand (char** arr, int* numberOfProcess, struct process* processArray){
//    printf("%d", *numberOfProcess);
//    for (int i = 0; i < *numberOfProcess; i++) {
//        if (processArray[i].done){
//            printf("%d %s DONE\n" ,processArray[i].pid, processArray[i].command);
//        } else {
//            printf("%d %s RUNING\n" ,processArray[i].pid ,processArray[i].command);
//        }
//    }
//    printf("test end his\n");
//}
//
//void checkIfBackground (char* instInString, char* arr[], int len, int* numberOfProcess, struct process* processArray) {
//    pid_t val;
//    int status;
//    int background = (strcmp(arr[len-2], "&") == 0); // 1 if background
//    *numberOfProcess = (*numberOfProcess) + 1;
//    val = fork();
//    if (val == -1) {
//        printError();
//    }
//    if (val > 1) { // this is the father
//        // insert to the process array before the fork!
//        ///////////////check what to do if this is invalid command//////////
//        struct process newP = {instInString, val, 0};
//        processArray[*numberOfProcess -1] = newP;
//        //test
//        for (int i = 0; i < *numberOfProcess ; i++) {
//            printf("test after insert: procces number: %d, pid: %d, command: %s done: %d\n", i, processArray[i].pid,
//                   processArray[i].command, processArray[i].done);
//        }
//        //until here
//        if (!background) { // the father need to wait for his son (specific son)
//            printf("test: father waiting\n");
//            waitpid(val, &status, 0);
//            printf("test: father stop waiting\n");
//        } else {
//            printf("test: father doesnt need to wait\n");
//        }
//    }
//
//    if (val == 0) { // this is the son
//        printf("%d\n", getpid());
//        printf("test %d\n", *numberOfProcess);
//        doCommand(arr, len, background, numberOfProcess, processArray);
//    }
//    //else- this is foreground and this is the father -continue
//    // after the father end- continue
//}
//
//
//
//void doCommand (char* arr[], int len, int background, int* numberOfProcess, struct process* processArray) {
//    if (background) {
//        char* arrayToExecv[len -1];
//        for (int i = 0; i < len -1; i++) {
//            arrayToExecv[i] = arr [i];
//        }
//        arrayToExecv[len-2] = NULL;
//        if (strcmp(arr[0], "exit") == 0 ) {
//            exitCommand(arrayToExecv, len -1);
//        }
//        else if (strcmp(arr[0], "cd") == 0 ) {
//            cdCommand(arrayToExecv, len-1);
//        }
//        else if (strcmp(arr[0], "jobs") == 0 ) {
//            jobsCommand(arrayToExecv, numberOfProcess, processArray);
//        }
//        else if (strcmp(arr[0], "history") == 0 ) {
//            historyCommand(arrayToExecv, numberOfProcess, processArray);
//        } else {
//            execCommand(arrayToExecv, len-1);
//        }
//    }
//    else {
//        char* arrayToExecv[len];
//        for (int i = 0; i < len; i++) {
//            arrayToExecv[i] = arr [i];
//        }
//        if (strcmp(arr[0], "exit") == 0 ) {
//            exitCommand(arrayToExecv, len);
//        }
//        else if (strcmp(arr[0], "cd") == 0 ) {
//            cdCommand(arrayToExecv, len);
//        }
//        else if (strcmp(arr[0], "jobs") == 0 ) {
//            jobsCommand(arrayToExecv, numberOfProcess, processArray);
//        }
//        else if (strcmp(arr[0], "history") == 0 ) {
//            printf("number od process %d\n" , *numberOfProcess);
//            historyCommand(arrayToExecv, numberOfProcess, processArray);
//        } else {
//            execCommand(arrayToExecv, len);
//        }
//    }
//
//}
//
//
//void execCommand(char* arr[], int len) {
//    int ret_code= execvp((char* const) arr[0], (char *const *) arr);
//    // if there was no error this code will not be executed
//    if (ret_code == -1)
//    {
//        printError();
//    }
//
//}
//
//
//void exitCommand (char** arr, int len){}
//
//
//void jobsCommand (char* arr[], int* numberOfProcess, struct process* processArray){
//    for (int i = 0; i <= *numberOfProcess; i++) {
//        if (!processArray[i].done) {
//            printf("%d %s\n", processArray[i].pid, processArray[i].command);
//        }
//    }
//}
//
//
//

////
//// Created by yuval on 4/28/20.
////








//if (!begin && word[strlen(word) -1] != '\"') {
//strcat(temp, word);
//} else if (!begin && word[strlen(word) -1] == '\"') {
//array[size] = temp;
//size++;
//begin = 1;
//}
//else if (word[0] == '\"' && begin) {
//begin = 0;
//strcat(temp, word);
//} else {
//array[size] = word;
//size++;
//}
//word = strtok (NULL, " ");



//
//#include <stdio.h>
//#include <string.h>
//
//#include <string.h>
//#include <stdio.h>
//#include <fcntl.h>
//#include <unistd.h>
//#include <wait.h>
//#include <stdlib.h>
//#include <ctype.h>
//
//
//
//void deleteChar(char* string, int idxToDel) {
//    memmove(&string[idxToDel], &string[idxToDel + 1], strlen(string) - idxToDel);
//
//}
//
//void removeSpacesBefore(char* text){
//    int c = 0;
//    while (text[c] != '\0') {
//        if (text[c] == ' ') {
//            deleteChar(text, c);
//        }
//    }
//}
//
//
//int main() {
//    char inst[100];
//    int i = 0;
//    // scan the instructions from the user
//    char* str = (char *)malloc(100 * sizeof(char));
//    if (str == NULL) {
//        fprintf(stderr, "Error in system call\n");
//    }
//    printf("> ");
//    fgets(str,100,stdin);
//    strcpy(inst, str);
//    char* token;
//    char* arr[1000];
//    str = strtok(str, "\n");
//    token = strtok(str, " ");
//    int size = 0;
//    while (token != NULL){
//        arr[size] = token;
//        token = strtok (NULL, " ");
//        size++;
//    }
//    for (int j= 0; j < size; j++) {
//        printf("%s\n", arr[j]);
//    }
//
//
//
//
//
//
//
//
////    //remove the "\n" from the string
////    str = strtok(str, "\n");
////    char *word = strtok (inst, " ");
////    char *array[100];
////    array[i] = word;
////    int lenUntilNewWord = (int) strlen(word) + 1;
////    // if the last word is not the last argument in the input
////    while (word[strlen(word) - 1] != '\n')
////    {
////        word = strtok (inst + lenUntilNewWord, " ");
////        i = i+1;
////        array[i] = word;
////        lenUntilNewWord += (int) strlen(word) + 1;
////    }
////    // removing the \n from the last cell
////    array[i] = strtok (array[i], "\n");
////    i++;
////    array[i] = NULL;
////    i++;
////    for (int j= 0; j < i-1; j++) {
////        printf("%s\n", array[j]);
////    }
//}
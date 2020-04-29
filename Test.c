////
//// Created by yuval on 4/28/20.
////
//
//#include <fcntl.h>
//#include <unistd.h>
//#include <wait.h>
//#include <stdio.h>
//#include <string.h>
//
//
//
//void copyStrings(char* dest, char* source) {
//    // nullify the array
//    for (int i = 0 ; i < 1000 ; i++) {
//        dest[i] = '\0';
//    }
//    for (int i =0  ; i < 1000; i++) {
//        dest[i] = source[i];
//    }
//}
//
//
//void removeMarks (char* string, char* withoutMarks) {
//    printf("%s\n", string);
//    for (int i = 0 ; i < 100; i++) {
//        withoutMarks[i] = '\0' ;
//    }
//    int i = 0;
//    if (string[0] == '"'){
//        while (string[i] != '\0') {
//            i++;
//        }
//        printf("%c\n", string[i -1] );
//        if (string[i -1] == '"') {
//            printf("%c\n", string[i -1] );
//            for (int j = 0 ; j < i - 2 ; j++) {
//                withoutMarks[j] = string[j+1];
//            }
//
//            copyStrings(string, withoutMarks);
//        }
//    }
//    printf("after %s\n", string);
//}
//
//int main() {
//    char* arr[2];
//    arr[0] = "echo";
//    arr[1] = "\"yu\"";
//    char withoutMarks[100];
//    if (strcmp(arr[0] , "echo") == 0) {
//        removeMarks(arr[1], withoutMarks);
//    }
////    printf("%s %s %s %s\n", arr[0], arr[1], arr[2], arr[3]);
//}
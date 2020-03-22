//-----------------------------------------------------------------------------
// Henry Nguyen
// CruzID: hnguye87
// Assignment: pa1
//-----------------------------------------------------------------------------
// Lex.c
// Indirectly sorts inputFile and prints it to outputFile
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[]){
    if ((argv[1] == NULL) || (argv[2] == NULL)){
        fprintf(stderr, "Error:  More than or less than two strings are given on the command line\n");
    }
    FILE *fp;
    char max[200];
    int n = 0; //count inputFile length
    int in = 0; //index

    //count number of lines in file
    fp = fopen(argv[1], "r");
    if(fp){
        while(!feof(fp)){
            fgets(max, 200, fp);
            n++;
        }
    }
    int arrayLength = n-1;
    int maxWordLength = 99; //max length for line in file
    char nums[arrayLength][maxWordLength];
    rewind(fp);

    //reads text from file into nums[in]
    while(!feof(fp)){
        fgets(nums[in], 200, fp);
        in++;
    }

    List A = newList();

    //Use List to indirectly sort the array
    for(int i = 0; i < n-1; i++)
    {
        moveFront(A);
        if(length(A) == 0){
            append(A, 0);
        }
        else{
            while(index(A) != -1){
                if(strcmp(nums[i], nums[get(A)]) <= 0){
                    insertBefore(A, i);
                    break;
                }
                moveNext(A);
                if(index(A) == -1){
                    append(A, i);
                }
            }
        }
    }
    fclose(fp);

    // writes the array in alphabetical order into outputFile
    fp = fopen(argv[2], "w");
    moveFront(A);
    for(int i = 0; i < arrayLength; i++){
      fprintf(fp, "%s", nums[get(A)]);
        moveNext(A);
   }
    fclose(fp);
    freeList(&A);

    return 0;

}

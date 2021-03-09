#include <stdio.h>
#include "list.h"
#include "stack.h"
#include "labirint.h"


void solutionLabirint(list l, stack s, char **mat){

}

void printLabirint(char **mat, int line, int column){
    int i, j;
    for(i=0;i<line;i++){
        for(j=0;j<column;j++)
            printf("%c",mat[i][j]);
        printf("\n");
    }
}
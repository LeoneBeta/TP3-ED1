#include <stdio.h>
#include "matriz.h"

void sizeMat(FILE *inputFile, int *line, int *column){
    int i, j;
    char sizeMat[10],stringLine[5],stringColumn[5];

    //Limpando o lixo de memória contido nas strings
    for(i=0;i<5;i++){
        sizeMat[i] = '\0';
        stringLine[i] = '\0';
        stringColumn[i] = '\0';
    }

    j = 0;
    i = 0;
    fgets(sizeMat,10,inputFile);
    do{
        if(sizeMat[i] != 'x' || sizeMat[i] != 'X')
            stringLine[j] = sizeMat[i];
        else
            break;
        j++;
        i++;
    }while(i<strlen(sizeMat));

    j = 0;
    i++;
    do{
        if(sizeMat[i] != '\0')
            stringColumn[j] = sizeMat[i];
        else
            break;
        j++;
        i++;
    }while(i<strlen(sizeMat));

    line = atoi(stringLine);
    column = atoi(stringColumn);
}

void allocMat(char **mat, int line, int column){
    int i;
    mat = (char*)malloc(line*sizeof(char));
    for(i=0;i<line;i++)
        mat[i] = (char*)malloc(column*sizeof(char));
}

void mountMat(FILE *inputeFile, char **mat, int column){
    int i,lin = 0;
    char *string;

    string = (char*)malloc(column*sizeof(char));

    fseek(inputeFile,0,SEEK_SET);
    while(fgets(string,column,inputeFile)){
        for(i=0;i<column;i++){
            mat[lin][i] = string[i];
        }
        lin++;
        fseek(inputeFile,0,SEEK_CUR);
    }
}

int checkIntegrity(char **mat, int line, int column){
    int lin,col, E = 0, S = 0, O = 0;
    //Percorre a primeira linha
    for(col=0;col<column;col++){
        if(mat[0][col] == 'E')
            E++;
        if(mat[0][col] == 'S')
            S++;
        if(mat[0][col] == '0')
            O++;
    }

    //Percorre a última linha
    for(col=0;col<column;col++){
        if(mat[line-1][col] == 'E')
            E++;
        if(mat[line-1][col] == 'S')
            S++;
        if(mat[line-1][col] == '0')
            O++;
    }

    //Percorre a primeira coluna
    for(lin=0;lin<line;lin++){
        if(mat[lin][0] == 'E')
            E++;
        if(mat[lin][0] == 'S')
            S++;
        if(mat[lin][0] == '0')
            O++;
    }

    //Percorre a ultima coluna
    for(lin=0;lin<line;lin++){
        if(mat[lin][column-1] == 'E')
            E++;
        if(mat[lin][column-1] == 'S')
            S++;
        if(mat[lin][column-1] == '0')
            O++;
    }

    if(E == 1 && S == 1 && O == 0)
        return 0; //Matriz integra com apenas uma Entrada, uma Saída, e nenhum "buraco" nas suas bordas
    if(E != 1)
        return 1; //Matriz com um número inválido de Entradas
    if(S != 1)
        return 2; //Matriz com um número inválido de Saídas
    if(0 != 0)
        return 3; //Matriz com algum "buraco" em sua borda
}

void endMat(char *mat, int line){
    int i, line;
    for (i=0; i < line; i++)
        free (mat[i]) ;
    free (mat) ;
}
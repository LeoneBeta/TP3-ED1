#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mLabirint.h"

void sizeMat(FILE *inputFile, int *line, int *column){
    int i, j;
    char size[10],stringLine[5],stringColumn[5];

    //Limpando o lixo de memória contido nas strings
    for(i=0;i<5;i++){
        stringLine[i] = '\0';
        stringColumn[i] = '\0';
    }
    for(i=0;i<10;i++)
        size[i] = '\0';

    j = 0;
    i = 0;
    fseek(inputFile,0,SEEK_SET);
    fgets(size,10,inputFile);
    do{
        if(size[i] != ' ')
            stringLine[j] = size[i];
        else
            break;
        j++;
        i++;
    }while(i<strlen(size));

    j = 0;
    i++;
    do{
        if(size[i] != '\n')
            stringColumn[j] = size[i];
        else
            break;
        j++;
        i++;
    }while(i<=strlen(size));

    *line = atoi(stringLine);
    *column = atoi(stringColumn);
}

void allocMat(char ***mat, int line, int column){
    int i = 0;
    *mat = malloc(line*sizeof(char*));
    for(i=0;i<line;i++)
        (*mat)[i] = (char*)malloc(column*sizeof(char));
}

void checkCoordinates(FILE *inputFile, int *e, int *s){
    int i, j;
    char coordinates[15], ex[3], ey[3], sx[3], sy[3];

    fseek(inputFile,0,SEEK_CUR);
    fgets(coordinates,15,inputFile);

    i = 0;
    j = 0;
    do{
        ex[j] = coordinates[i];
        i++;
        j++;  
    }while(coordinates[i] != ' ');

    i++;
    j = 0;
    do{
        ey[j] = coordinates[i];
        i++;
        j++;
    }while(coordinates[i] != ' ');
    
    i++;
    j = 0;
    do{
        sx[j] = coordinates[i];
        i++;
        j++;
    }while(coordinates[i] != ' ');

    i++;
    j = 0;
    do{
        sy[j] = coordinates[i];
        i++;
        j++;
    }while(coordinates[i] != '\n');

    e[0] = atoi(ex);
    e[1] = atoi(ey);
    s[0] = atoi(sx);
    s[1] = atoi(sy);
}

void mountMat(FILE *inputeFile, char ***mat, int column, int *e, int *s){
    int i,lin = 0;
    char *string;

    string = (char*)malloc(column*sizeof(char));

    /*Problema de falha de segmentação, o comando fgets está copiando apenas 9 caracteres para a 
    variavel string*/

    //Testar o fgets com column+1

    fseek(inputeFile,0,SEEK_CUR);
    while(fgets(string,column+1,inputeFile)){
        for(i=0;i<column;i++){
            (*mat)[lin][i] = string[i];
        }
        lin++;
        fseek(inputeFile,1,SEEK_CUR);
        fseek(inputeFile,0,SEEK_CUR);
    }

    //Inserindo as letras E e S na Entrada e Saída do Labirinto
    (*mat)[e[0]][e[1]] = 'E';
    (*mat)[s[0]][s[1]] = 'S';
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
    if(O != 0)
        return 3; //Matriz com algum "buraco" em sua borda
}

void endMat(char **mat, int line){
    int i;
    for (i=0;i<line;i++)
        free(mat[i]);
    free(mat);
}
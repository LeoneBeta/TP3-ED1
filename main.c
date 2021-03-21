#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "utilities.h"
#include "stack.h"
#include "list.h"
#include "mLabirint.h"
#include "labirint.h"

int main(){
    setlocale(LC_ALL,"portuguese");
    
    FILE *inputFile, *outputFile;

    TList *l = (TList*)malloc(sizeof(TList));
    TStack *s = (TStack*)malloc(sizeof(TStack));

    char nameInputFile[20], nameOutputFile[20];
    
    int i, j, integrity;

    //Matriz
    char **mat;
    int line,column;
    int coordinatesE[2], coordinatesS[2];
    int *ptrE, *ptrS;

    ptrE = &coordinatesE;
    ptrS = &coordinatesS;

    setbuf(stdin,NULL);
    printf("Nome do arquivo de entrada: ");
    fgets(nameInputFile,20,stdin);
    removeEnter(nameInputFile);
    setbuf(stdin,NULL);
    printf("Nome do arquivo de saída: ");
    fgets(nameOutputFile,20,stdin);
    removeEnter(nameOutputFile);

    //Abertura do arquiv de Entrada e verificação
    inputFile = fopen(nameInputFile,"a+");
    if(!inputFile)
        printf("Falha ao abrir o arquivo de Entrada %s",nameInputFile);
    
    outputFile = fopen(nameOutputFile,"a+");
    if(!outputFile)
        printf("Falha ao abrir o arquivo de Saída %s",nameOutputFile);
    
    //Faz a leitura da primeira linha do arquivo onde contám o tamanho da matriz
    sizeMat(inputFile,&line,&column);
    printf("\nNúmero de Linhas: %d",line);
    printf("\nNúmero de Colunas: %d",column);
    
    //Aloca a Matriz dinâmica
    allocMat(mat,line,column);

    //Faz a leitura da segunda linha da Matriz onde contém as coordenadas de Entrada e Saída
    checkCoordinates(inputFile,ptrE,ptrS);


    //Monta a matriz retirando os dados do arquivo de entrada
    mountMat(inputFile,mat,column,ptrE,ptrS);

    //Setar a entrada e saida com as letras E e S nas suas determinadas posições
    
    //Checa a Integridade da matriz
    //Retornos da Função
    //0 = Integra
    //1 = Numero inválido de Entradas
    //2 = Número inválido de Saidas
    //3 = Existe algum "buraco" nas bordas da matriz
    integrity = checkIntegrity(mat,line,column);
    if(integrity == 0)
        printf("\nMatriz Integra");
    if(integrity == 1)
        printf("\nNúmero inválido de Entradas");
    if(integrity == 2)
        printf("\nNúmero inválido de Saídas");
    if(integrity == 3)
        printf("\nMatriz contém uma falha nas suas bordas");

    /*
    //Desenvolver a etapa de resolução do labirinto
    //Caso a Matriz fornecida não for válida, o programa finaliza
    if(integrity != 0)
        return 0;
    solutionLabirint(l,s,*mat);
    
    */
    printf("\nMatriz fornecida no arquivo %s",nameInputFile);
    printLabirint(mat,line,column);

    /*Desenvolver a etapa de printar os resultados */

    /*Desenvolver a etapa de armazenar os resultados em arquivo*/


    //Desaloca a Matriz
    endMat(mat,line);

    //Fecha os arquivos
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
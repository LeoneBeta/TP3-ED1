#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "stack.h"
#include "labirint.h"


void solutionLabirint(list l, stack s, char **mat, int *ptrE, int line, int column){
    int i,j,exit = 0;
    TElementStack eStack;
    TElementList eList;

    //Inicializando a primeira coordenada a inserindo na lista
    eList.coordX = ptrE[0];
    eList.coordY = ptrE[1]; 
    insertEnd(l,eList);

    eStack.coordX = ptrE[0];
    eStack.coordY = ptrE[1];
    eStack.lastMove = 0;
    eStack.exit = 0;
    //Passando a posição atual para a lista onde armazena os locais ja passados pelo robo
    
    do{
        //Zerando todo conteudo do elemento atual
        eStack.left = 0;
        eStack.up = 0;
        eStack.right = 0;
        eStack.down = 0;
        
        //Verificando os possiveis caminhos da coordenada atual e comparando se o caminho seguinte já foi percorrido
        //Caso ambas as validações forem verdadeiras, é um caminho possível
        //Esquerda
        if(eStack.coordY-1 >= 0 && mat[eStack.coordX][eStack.coordY-1] != '#' && !compareCoordinates(l,eStack.coordX,eStack.coordY-1) && eStack.lastMove != 3)
            eStack.left = 1;
        //Direita
        if(eStack.coordY+1 <= column-1 && mat[eStack.coordX][eStack.coordY+1] != '#' && !compareCoordinates(l,eStack.coordX,eStack.coordY+1) && eStack.lastMove != 1)
            eStack.right = 1;
        //Cima
        if(eStack.coordX-1 >=0 && mat[eStack.coordX-1][eStack.coordY] != '#' && !compareCoordinates(l,eStack.coordX-1,eStack.coordY) && eStack.lastMove != 4 )
                eStack.up = 1;
        //Baixo
        if(eStack.coordX+1 <= line-1 && mat[eStack.coordX+1][eStack.coordY] != '#' && !compareCoordinates(l,eStack.coordX+1,eStack.coordY) && eStack.lastMove != 2)
                eStack.down = 1;

        //Inserindo a coordenada atual com suas possiveis movimentações na pilha
        push(s,eStack);

        //Se a coodenada atual do robo for igual a S ele encontrou a saida
        if(mat[eStack.coordX][eStack.coordY] == 'S'){
            exit = 1;
            s->top->info.exit = 1;
            break;
        }

        //Verificando se existe movimentos possíveis
        if(s->top->info.left == 1 || s->top->info.right == 1 || s->top->info.up == 1 || s->top->info.down == 1){
            move(l,s,&eStack);
        }else{ //Caso não hover movimentações possiveis, o robo retorna até a ultima encrusilhada
            turnBack(l,s,&eStack);
        }

        //Caso o retorno do caminho esvazie a pilha, quer dizer que não tem caminhos possíveis no labirinto
        if(!s->top){
            printf("\nSem caminhos possíveis");
            break;
        }

    }while(exit != 1);
}

void move(list l, stack s, TElementStack *eStack){
    //Verifica qual foi o ultimo movimento feito para que o robo não retorne e fique preso em loop
    switch (eStack->lastMove){
    case 0:
        if(eStack->left == 1){    //mover para esquerda
            moveLeft(l,s,eStack);
        }else{
            if(eStack->right == 1){   //Mover para cima
                moveRight(l,s,eStack);
            }else{
                if(eStack->up == 1){      //Mover para direita
                    moveUp(l,s,eStack);
                }else{
                    if(eStack->down == 1){    //Mover para baixo
                        moveDown(l,s,eStack);
                    }
                }
            }
        }
        break;
    case 1: //Ultimo movimento foi para esquerda
        if(eStack->left == 1){    //mover para esquerda
            moveLeft(l,s,eStack);
        }else{
            if(eStack->up == 1){      //Mover para cima
                moveUp(l,s,eStack);
            }else{
                if(eStack->down == 1){    //Mover para baixo
                    moveDown(l,s,eStack);
                }
            }
        }
        break;
    case 2: //Ultimo movimento foi para cima
        if(eStack->left == 1){    //mover para esquerda
            moveLeft(l,s,eStack);
        }else{
            if(eStack->right == 1){      //Mover para cima
                moveRight(l,s,eStack);
            }else{
                if(eStack->up == 1){   //Mover para direita
                    moveUp(l,s,eStack);
                }
            }
        }
        break;
    case 3: //Ultimo movimento foi para direita
            if(eStack->right == 1){      //Mover para cima
                moveRight(l,s,eStack);
            }else{
                if(eStack->up == 1){   //Mover para direita
                    moveUp(l,s,eStack);
                }else{
                    if(eStack->down == 1){    //Mover para baixo
                        moveDown(l,s,eStack);
                    }
                }
            }
        break;
    case 4: //Ultimo movimento foi para baixo
            if(eStack->left == 1){    //mover para esquerda
                moveLeft(l,s,eStack);
            }else{
                if(eStack->right == 1){   //Mover para direita
                    moveRight(l,s,eStack);
                }else{
                    if(eStack->down == 1){    //Mover para baixo
                        moveDown(l,s,eStack);
                    }
                }
            }
        break;
    }

}

void moveLeft(list l, stack s, TElementStack *eStack){
    TElementList eList;
    eStack->coordY -=1;
    eStack->lastMove = 1;
    s->top->info.left = 0;
    eList.coordX = eStack->coordX;
    eList.coordY = eStack->coordY;
    insertEnd(l,eList);
}

void moveRight(list l, stack s, TElementStack *eStack){
    TElementList eList;
    eStack->coordY +=1;
    eStack->lastMove = 3;
    s->top->info.right = 0;
    eList.coordX = eStack->coordX;
    eList.coordY = eStack->coordY;
    insertEnd(l,eList);
}

void moveUp(list l, stack s, TElementStack *eStack){
    TElementList eList;
    eStack->coordX -=1;
    eStack->lastMove = 2;
    s->top->info.up = 0;
    eList.coordX = eStack->coordX;
    eList.coordY = eStack->coordY;
    insertEnd(l,eList);
}

void moveDown(list l, stack s, TElementStack *eStack){
    TElementList eList;
    eStack->coordX +=1;
    eStack->lastMove = 4;
    s->top->info.down = 0;
    eList.coordX = eStack->coordX;
    eList.coordY = eStack->coordY;
    insertEnd(l,eList);
}

int turnBack(list l, stack s, TElementStack *eStack){
    int crossroads = 0;
    do{
        if(!s->size)
            break;
        if(s->top->info.left == 0 && s->top->info.up == 0 && s->top->info.right == 0 && s->top->info.down == 0)
            pop(s,eStack);
        else
            crossroads = 1;
    }while(crossroads != 1);

    //Reseto a struct eStack para a coordenada atual do topo da pilha e chamo o move para continuar a movimentaçaõ
    eStack->coordX = s->top->info.coordX;
    eStack->coordY = s->top->info.coordY;
    eStack->left = s->top->info.left;
    eStack->up = s->top->info.up;
    eStack->right = s->top->info.right;
    eStack->down = s->top->info.down;
    eStack->lastMove = s->top->info.lastMove;

    move(l,s,eStack);
}

int compareCoordinates(list l, int coordX, int coordY){
    int i=0;
    l->current = l->first;
    do{
        if(l->current->info.coordX == coordX && l->current->info.coordY == coordY)
            return 1;   //Retorna 1 se encontrar uma coordenada igual na lista de caminho ja percorrido
        l->current = l->current->next;
        i++;
    }while(i<l->size);
    return 0;           //Retorna 0 caso não encontre uma coordenada igual na lista
}

void createPath(stack s, char ***mat,int line, int column, int *ptrE, int *ptrS){
    int i,j;
    TElementStack e;
    for(i=0;i<line;i++){
        for(j=0;j<column;j++){
            (*mat)[i][j] = '#';
        }
    }
    do{
        pop(s,&e);
        (*mat)[e.coordX][e.coordY] = '0';
    }while(s->size != 0);
}

void printLabirint(char **mat, int line, int column){
    int i, j;
    for(i=0;i<line;i++){
        for(j=0;j<column;j++)
            printf("%c",mat[i][j]);
        printf("\n");
    }
}
#include <stdio.h>
#include "list.h"
#include "stack.h"
#include "labirint.h"


void solutionLabirint(list l, stack s, char **mat, int *ptrE){
    int exit = 0;
    int i,j;
    TElementStack *eStack, *eCompareStack;
    TElementList *eList;

    eStack->coordX = ptrE[0];
    eStack->coordY = ptrE[1];
    eStack->lastMove = 0;
    //Passando a posição atual para a lista onde armazena os locais ja passados pelo robo
    eList->coordX = eStack->coordX;
    eList->coordY = eStack->coordY;
    insertEnd(l,*eList);
    
    do{
        //Zerando todo conteudo do elemento atual
        eStack->left = 0;
        eStack->up = 0;
        eStack->right = 0;
        eStack->down = 0;

        eCompareStack->coordX = eStack->coordX;
        eCompareStack->coordY = eStack->coordY;

        //Verificando os possiveis caminhos da coordenada atual e comparando se o caminho seguinte já foi percorrido
        //Caso ambas as validações forem verdadeiras, é um caminho possível
        //Esquerda
        if(mat[eStack->coordX][eStack->coordY-1] == '0'){
            eCompareStack->coordY--;
            if(!compareCoordinates(l,eCompareStack))
                eStack->left = 1;
        }
        //Cima
        if(mat[eStack->coordX-1][eStack->coordY] == '0'){
            eCompareStack->coordX--;
            if(!compareCoordinates(l,eCompareStack))
                eStack->up = 1;
        }
        //Direita
        if(mat[eStack->coordX][eStack->coordY+1] == '0'){
            eCompareStack->coordY++;
            if(!compareCoordinates(l,eCompareStack))
                eStack->right = 1;
        }
        //Baixo
        if(mat[eStack->coordX+1][eStack->coordY] == '0'){
            eCompareStack->coordX++;
            if(!compareCoordinates(l,eCompareStack))   
                eStack->down = 1;
        }
        //Inserindo a coordenada atual com suas possiveis movimentações na pilha
        push(s,*eStack);

        //Se a coodenada atual do robo for igual a S ele encontrou a saida
        if(mat[eStack->coordX][eStack->coordY] == 'S'){
            exit = 1;
            break;
        }

        //Verificando se existe movimentos possíveis
        if(eStack->left == '1' || eStack->up == '1' || eStack->right == '1' || eStack->down == '1'){
            move(l,s,eStack);
        }else{ //Caso não hover movimentações possiveis, o robo retorna até a ultima encrusilhada
            turnBack(l,s,eStack);
        }
    }while(exit != 1);
}

void move(list l, stack s, TElementStack *eStack){
    //Verifica qual foi o ultimo movimento feito para que o robo não retorne e fique preso em loop
    switch (eStack->lastMove){
    case 0:
        if(eStack->left == '1'){    //mover para esquerda
            moveLeft(l,s,eStack);
        }else{
            if(eStack->up == '1'){      //Mover para cima
                moveUp(l,s,eStack);
            }else{
                if(eStack->right == '1'){   //Mover para direita
                    moveRight(l,s,eStack);
                }else{
                    if(eStack->down == '1'){    //Mover para baixo
                        moveDown(l,s,eStack);
                    }
                }
            }
        }
        break;
    case 1: //Ultimo movimento foi para esquerda
        if(eStack->left == '1'){    //mover para esquerda
            moveLeft(l,s,eStack);
        }else{
            if(eStack->up == '1'){      //Mover para cima
                moveUp(l,s,eStack);
            }else{
                if(eStack->down == '1'){    //Mover para baixo
                    moveDown(l,s,eStack);
                }
            }
        }
        break;
    case 2: //Ultimo movimento foi para cima
        if(eStack->left == '1'){    //mover para esquerda
            moveLeft(l,s,eStack);
        }else{
            if(eStack->up == '1'){      //Mover para cima
                moveUp(l,s,eStack);
            }else{
                if(eStack->right == '1'){   //Mover para direita
                    moveRight(l,s,eStack);
                }
            }
        }
        break;
    case 3: //Ultimo movimento foi para direita
            if(eStack->up == '1'){      //Mover para cima
                moveUp(l,s,eStack);
            }else{
                if(eStack->right == '1'){   //Mover para direita
                    moveRight(l,s,eStack);
                }else{
                    if(eStack->down == '1'){    //Mover para baixo
                        moveDown(l,s,eStack);
                    }
                }
            }
        break;
    case 4: //Ultimo movimento foi para baixo
            if(eStack->left == '1'){    //mover para esquerda
                moveLeft(l,s,eStack);
            }else{
                if(eStack->right == '1'){   //Mover para direita
                    moveRight(l,s,eStack);
                }else{
                    if(eStack->down == '1'){    //Mover para baixo
                        moveDown(l,s,eStack);
                    }
                }
            }
        break;
    }

}

void moveLeft(list l, stack s, TElementStack *eStack){
    TElementList *eList;
    eStack->coordY -=1;
    eStack->lastMove == 1;
    s->top->info.left = 0;
    eList->coordX = eStack->coordX;
    eList->coordY = eStack->coordX;
    insertEnd(l,*eList);
}

void moveUp(list l, stack s, TElementStack *eStack){
    TElementList *eList;
    eStack->coordX -=1;
    eStack->lastMove == 2;
    s->top->info.up = 0;
    eList->coordX = eStack->coordX;
    eList->coordY = eStack->coordX;
    insertEnd(l,*eList);
}

void moveRight(list l, stack s, TElementStack *eStack){
    TElementList *eList;
    eStack->coordY +=1;
    eStack->lastMove == 3;
    s->top->info.right = 0;
    eList->coordX = eStack->coordX;
    eList->coordY = eStack->coordX;
    insertEnd(l,*eList);
}

void moveDown(list l, stack s, TElementStack *eStack){
    TElementList *eList;
    eStack->coordX +=1;
    eStack->lastMove == 4;
    s->top->info.down = 0;
    eList->coordX = eStack->coordX;
    eList->coordY = eStack->coordX;
    insertEnd(l,*eList);
    
}

void turnBack(list l, stack s, TElementStack *eStack){}

int compareCoordinates(list l, TElementStack *eStack){
    int i=0;
    l->current = l->first;
    do{
        if(l->current->info.coordX == eStack->coordX && l->current->info.coordY == eStack->coordY)
            return 1;   //Retorna 1 se encontrar uma coordenada igual na lista de caminho ja percorrido
        l->current = l->current->next;
    }while(i<l->size);
    return 0;           //Retorna 0 caso não encontre uma coordenada igual na lista
}

void printLabirint(char **mat, int line, int column){
    int i, j;
    for(i=0;i<line;i++){
        for(j=0;j<column;j++)
            printf("%c",mat[i][j]);
        printf("\n");
    }
}
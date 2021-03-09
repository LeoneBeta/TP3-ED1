#include <stdio.h>
#include <stdlib.h>
#include "list.h"

list creatList(){
    list l = (list)malloc(sizeof(TList));
    if(l){
        l->size = 0;
        l->first = NULL;
        l->last = NULL;
        l->current = NULL;
    }
    return l;
}

int insertStart(list l, TElementList e){
    TNodoList *n;
    n = (TNodoList*)malloc(sizeof(TNodoList));
    if(n){
        n->info = e;
        n->next = l->first;
        n->prior = NULL;
        if(l->first)
            l->first->prior = n;
        else
            l->last = n;
        l->first = n;
        l->size++;
        return 1;
    }else
        return 0;
}

int insertEnd(list l, TElementList e){
    TNodoList *n;
    if(l->first == NULL)
        return insertStart(l,e);

    n = (TNodoList*)malloc(sizeof(TNodoList));
    if(n){
        n->info = e;
        n->next = NULL;
        n->prior = l->last;
        l->last->next = n;
        l->last = n;
        l->size++;
        return 1;
    }else
        return 0;
}

int insertPosition(list l, TElementList e, int position){
    TNodoList *n, *nAux, *ant;
    int i;

    if(position == 1)
        return insertStart(l,e);
    else
        if(position == l->size+1)
            return insertEnd(l,e);
        else
            if(position < 1 || position > l->size +1)
                return 0;
            else{
                n = (TNodoList*)malloc(sizeof(TNodoList));
                if(!n)
                    return 0;
                n->info = e;
                nAux = l->first;
                for(i=1;i<position;i++)
                    nAux = nAux->next;
                n->next = nAux;
                n->prior = nAux->prior;
                nAux->prior->next = n;
                nAux->prior = n;
                l->size++;
                return 1;
            }
}

int removeElement(list l, TKeyList key, TElementList *e){
    TNodoList *n;
    n = l->first;

    while(n){
        if(n->info.key == key){
            if(l->size == 1){ //A Lista possui um unico Nodo
                l->first = NULL;
                l->last = NULL;
            }else
                if(n == l->first){ //Removendo o primeiro Nodo
                    l->first = l->first->next;
                    l->first->prior = NULL;
                }else
                    if(n == l->last){ //Removendo o último Nodo
                        l->last = l->last->prior;
                        l->last->next = NULL;
                    }else{ //Removendo um Nodo interno
                        n->prior->next = n->next;
                        n->next->prior = n->prior;
                    }
                    *e = n->info;
                    free(n);
                    return 1;
        }else{
            n = n->next;
        }
    }
    return 0;
}

void deleteList(list l){
    TNodoList *n;
    while(l->first){
        n = l->first;
        l->first = l->first->next;
        free(n);
    }
    free(l);
}

int getElement(list l, int position, TElementList *e){
    int i;
    TNodoList *n;

    if(position < 1 || position > l->size)
        return 0;
    
    if(position <= l->size/2){ //Separa a lista em 2 facilitando a busca
        for(i=1;i<position;i++)
            n = n->next;
        *e = n->info;
    }else{
        for(i=l->size;i>position;i--)
            n = n->prior;
        *e = n->info;
    }
    return 1;
}

int setCurrent(list l, int position){
    int i;
    if(position < 1 | position > l->size)
        return 0;
    if(position < l->size/2){
        l->current = l->first;
        for(i=1;i<position;i++)
            l->current = l->current->next;
    }else{
        l->current = l->last;
        for(i=l->size;i>position;i++)
            l->current = l->current->prior;
    }
    return 1;
}

int getCurrent(list l, TElementList *e){
    if(l->current){
        *e = l->current->info;
        l->current = l->current->next;
        return 1;
    }else
        return 0;
}

int emptyList(list l){
    return l->first == NULL;
}

int fullList(list l){
    TNodoList *n;
    n = (TNodoList*)malloc(sizeof(TNodoList));
    if(n){
        free(n);
        return 0;
    }else 
        return 1;
}

int getSize(list l){
    return l->size;
}
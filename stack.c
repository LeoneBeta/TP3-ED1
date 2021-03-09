#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


stack creatStack(){
    stack s = (stack)malloc(sizeof(TStack));
    if(s){
        s->top = NULL;
        s->size = 0;
    }
    return s;
}

void endStack(stack s){
    TNodoStack *n;
    while(s->top){
        n = s->top;
        s->top = s->top->next;
        free(n);
    }
    free(s);
}

int push(stack s,TElementStack e){
    TNodoStack *n;
    n = (TNodoStack*)malloc(sizeof(TNodoStack));
    if(!n)
        return 0;
    n->info = e;
    n->next = s->top;
    s->top = n;
    s->size++;
    return 1;
}

int pop(stack s,TElementStack *e){
    TNodoStack *n;
    if(!s->top)
        return 0;
    n = s->top;
    s->top = s->top->next;
    *e = n->info;
    free(n);
    s->size--;
    return 1;
}

int fullStack(stack s){
    TNodoStack *n;
    n = (TNodoStack*)malloc(sizeof(TNodoStack));
    if(n == NULL)
        return 1;
    free(n);
    return 0;
}

int emptyStack(stack s){
    return !s->size;
}

int sizeStack(stack s){
    return s->size;
}
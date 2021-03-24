#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef struct{
    int coordX,coordY;
    int left,up,right,down;
    int lastMove;
    int exit;
}TElementStack;

typedef struct NodoStack{
    TElementStack info;
    struct NodoStack *next;
}TNodoStack;

typedef struct{
    TNodoStack *top;
    int size;
}TStack;
typedef TStack *stack;

stack creatStack();
void endStack(stack);
int push(stack,TElementStack);
int pop(stack,TElementStack*);
void invertStack(stack,stack);
int fullStack(stack);
int emptyStack(stack);
int sizeStack(stack);


#endif
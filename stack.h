#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef char TKeyStack;
typedef struct{
    TKeyStack key;
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
int fullStack(stack);
int emptyStack(stack);
int sizeStack(stack);


#endif
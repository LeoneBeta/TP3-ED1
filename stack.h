#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef char TKey;
typedef struct{
    TKey key;
}TElement;

typedef struct Nodo{
    TElement info;
    struct Nodo *next;
}TNodo;

typedef struct{
    TNodo *top;
    int size;
}TStack;
typedef TStack *stack;

stack creatStack();
void endStack(stack);
int push(stack,TElement);
int pop(stack,TElement*);
int fullStack(stack);
int emptyStack(stack);
int sizeStack(stack);


#endif
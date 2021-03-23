#ifndef LABIRINT_H_INCLUDED
#define LABIRINT_H_INCLUDED

void solutionLabirint(list,stack,char**,int*,int*);
void move(list,stack,TElementStack*);
void moveLeft(list,stack,TElementStack*);
void moveUp(list,stack,TElementStack*);
void moveRight(list,stack,TElementStack*);
void moveDown(list,stack,TElementStack*);
void turnBack(list,stack,TElementStack*);
void printLabirint(char**,int,int);

#endif
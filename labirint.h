#ifndef LABIRINT_H_INCLUDED
#define LABIRINT_H_INCLUDED

void solutionLabirint(list,stack,char**,int*,int,int);
void move(list,stack,TElementStack*);
void moveLeft(list,stack,TElementStack*);
void moveUp(list,stack,TElementStack*);
void moveRight(list,stack,TElementStack*);
void moveDown(list,stack,TElementStack*);
int turnBack(list,stack,TElementStack*);
int compareCoordinates(list,int,int);
void pathList(list,stack);
void path(list,char***,int,int);
void printLabirint(char**,int,int);

#endif
#ifndef MLABIRINT_H_INCLUDED
#define MLABIRINT_H_INCLUDED

void sizeMat(FILE*,int*,int*);
void allocMat(char**,int,int);
void mountMat(FILE*,char**,int);
int checkIntegrity(char**,int,int);
void endMat(char**,int);
#endif
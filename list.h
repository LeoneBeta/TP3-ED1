#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED


typedef int TKeyList;
typedef struct{
    TKeyList key;
}TElementList;

typedef struct NodoList{
    TElementList info;
    struct NodoList *prior, *next;
}TNodoList;

typedef struct{
    TNodoList *first, *last, *current;
    int size;
}TList;

typedef TList *list;


list creatList();
int insertStart(list,TElementList);
int insertEnd(list,TElementList);
int insertPosition(list,TElementList,int);
int removeElement(list,TKeyList,TElementList*);
void deleteList(list);
int getElement(list,int,TElementList*);
int emptyList(list);
int fullList(list);
int setCurrent(list,int);
int getCurrent(list,TElementList*);

#endif
#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED


typedef int TKey;
typedef struct{
    TKey key;
}TElement;

typedef struct Nodo{
    TElement info;
    struct Nodo *prior, *next;
}TNodo;

typedef struct{
    TNodo *first, *last, *current;
    int size;
}TList;

typedef TList *list;


list creatList();
int insertStart(list,TElement);
int insertEnd(list,TElement);
int insertPosition(list,TElement,int);
int removeElement(list,TKey,TElement*);
void deleteList(list);
int getElement(list,int,TElement*);
int emptyList(list);
int fullList(list);
int setCurrent(list,int);
int getCurrent(list,TElement*);

#endif
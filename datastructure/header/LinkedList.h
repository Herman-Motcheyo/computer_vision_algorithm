#ifndef __LINKEDLIST__
#define __LINKEDLIST__

#include "Point.h"

typedef struct LinkedList
{
    struct Point head ;
    struct LinkedList* next ;
} LinkedList;

//permet d'initialiser une liste
LinkedList* new_LinkedList();

//permet de faire une insertion en queue 
void queue_Insertion(LinkedList* , Point);

void free_LinkedList(LinkedList*);
Point* get_Point(int position);

//permet d'afficher les elements de la liste
void print_LiskedList(LinkedList*);
int isEmptyList(LinkedList*);
LinkedList* deleteElement(Point *p );
#endif
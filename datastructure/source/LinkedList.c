#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../header/LinkedList.h"

LinkedList *new_LinkedList()
{
    LinkedList *l = (LinkedList *)malloc(sizeof(LinkedList));
    if (l == NULL)
    {
        printf("Probleme d'allocation Memoire \n");
        exit(1);
    }
    l->head.x = 0;
    l->head.y = 0;
    l->head.intensite = 0;
    l->next = NULL;
    printf("Allocation reussi  de la liste chainée reussie\n");

    return l;
}

void queue_Insertion(LinkedList *list, Point p)
{
    LinkedList *tmp = list;
    if (list->next == NULL)
    {
        list->head = p;
        list->next = NULL;
    }
    else
    {
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
       tmp->next = list;
    }
}
void free_LinkedList(LinkedList *);
Point *get_Point(int position);
void print_LiskedList(LinkedList *list)
{
        while (list->next != NULL)
        {
            printf(" p(%d , %d ), %d)", list->head.x, list->head.y, list->head.intensite);
            list = list->next;
        }
}
int isEmptyList(LinkedList *);
LinkedList *deleteElement(Point *p);
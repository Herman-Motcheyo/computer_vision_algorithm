#ifndef LINKED_LIST_c
#define LINKED_LIST_c

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "../header/LinkedList.h"

List new_list(void)
{
    List li = malloc(sizeof(List_element));
    li->length = 0;
    li->queue = NULL;
    li->head = NULL;

    return li;
}

boolean is_empty_list(List li)
{
    if (li->head == NULL && li->queue == NULL)
    {
        return True;
    }
    return False;
}

void print_list(List li, void print_value(void *value, boolean last))
{
    if (is_empty_list(li) == True)
    {
        printf("vide");
    }
    else
    {
        typedef struct element element;
        element *temp = li->head;
        printf("(");
        while (temp != NULL)
        {
            if (temp->next == NULL)
            {
                print_value(temp->value, True);
            }
            else
            {
                print_value(temp->value, False);
            }
            temp = temp->next;
        }
        printf(")");
    }
}

void queue_insertion(List li, void *x)
{
    typedef struct element element;
    li->length++;
    element *elem = malloc(sizeof(element));
    elem->next = NULL;
    elem->value = x;
    if (is_empty_list(li) == True)
    {
        li->head = elem;
        li->queue = elem;
    }
    else
    {
        element *temp = li->head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = elem;
        li->queue = elem;
    }
}

void head_insertion(List li, void *x)
{
    typedef struct element element;
    li->length++;
    element *elem = malloc(sizeof(element));
    elem->next = NULL;
    elem->value = x;
    if (is_empty_list(li) == True)
    {
        li->head = elem;
        li->queue = elem;
    }
    else
    {
        elem->next = li->head;
        li->head = elem;
    }
}

void *get_element_list(List li, int index)
{
    typedef struct element element;
    if (index >= li->length)
    {
        return NULL;
    }
    else
    {
        int i = 0;
        element *elem = li->head;
        while (i < index)
        {
            elem = elem->next;
            i++;
        }
        return elem->value;
    }
}

boolean search_value_in_list(List li, void *x, boolean equal(void *val1, void *val2 , ...) , ...)
{
    typedef struct element element;
    element *elem = li->head;

    va_list lst;
    va_start(lst, equal);
    int permut = va_arg(lst, int);
    va_end(lst);

   
    while (elem != NULL)
    {
        if (equal(elem->value, x , permut) == 0)
        {
            return True;
        }
        elem = elem->next;
    }

    return False;
}

void delete_element_list(List li, int index)
{
    if (index < li->length)
    {
        int cmpt = 0;
        typedef struct element element;
        element *elem = li->head;
        element *precedent = NULL;
        element *next = NULL;
        while (cmpt != index)
        {
            precedent = elem;
            elem = elem->next;
            cmpt++;
        }

        next = elem->next;
        if (next != NULL && precedent != NULL)
        {
            precedent->next = next;
        }
        else if (precedent == NULL && next != NULL)
        {
            li->head = next;
        }
        else if (precedent == NULL && next == NULL)
        {
            li->head = NULL;
            li->queue = NULL;
        }
        else
        {
            precedent->next = NULL;
        }

        if (li->length > 0)
        {
            li->length -= 1;
        }

        free(elem);
    }
}

List copy_element_list(List li)
{
    typedef struct element element;
    element *elem = li->head;
    List list_result = new_list();
    while (elem != NULL)
    {
        queue_insertion(list_result, elem->value);
        elem = elem->next;
    }
    return list_result;
}

boolean include_value_list(List li1, List li2,  boolean equal(void *val1, void *val2 , ...))
{

    typedef struct element element;
    element *elem2 = li2->head;
    boolean find = False;
    while(elem2 != NULL)
    {
        element *elem1 = li1->head;
        while(elem1 != NULL && find == False){

            if(equal(elem1->value , elem2->value) == True){
                find = True;
            }
            elem1 = elem1->next;
        }

        if(find == False){
            return False;
        }

        find = False;

        elem2 = elem2->next;
    }

    return True;
}

int get_index_element_list(List li, void *value, boolean equal(void *val1, void *val2 , ...))
{
    typedef struct element element;
    element *elem = li->head;
    int index = 0;
    while (elem != NULL)
    {
        if (equal(elem->value, value) == 0)
        {
            return index;
        }
        elem = elem->next;
        index++;
    }

    return -1;
}

void free_list(List li)
{
    if (li != NULL)
    {
        if (is_empty_list(li) == False)
        {
            typedef struct element element;
            element *elem = li->head;
            while (elem != NULL)
            {
                element *temp = elem;
                elem = elem->next;
                free(temp);
                temp = NULL;
            }
        }
        free(li);
    }
}

#endif
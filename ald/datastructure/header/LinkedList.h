#ifndef __LINKEDLIST__
#define __LINKEDLIST__
#include "../header/structure.h"

typedef struct List
{
    struct element *head;
    struct element *queue;
    int length;
} *List , List_element;


List new_list(void);
boolean is_empty_list(List li);
boolean search_value_in_list(List li, void *value, boolean equal(void *val1, void *val2 , ...) , ...);
int get_index_element_list(List li, void *value, boolean equal(void *val1, void *val2 , ...));
void print_list(List li, void print_value(void *value , boolean last));
void queue_insertion(List li, void *x);
void head_insertion(List li, void *x);
void *get_element_list(List li , int index);
List copy_element_list(List li);
boolean include_value_list(List li1, List li2, boolean equal(void *val1, void *val2 , ...));
void delete_element_list(List li , int index);
void free_list(List li);

#endif 
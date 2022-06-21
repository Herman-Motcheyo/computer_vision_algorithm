#ifndef STACK_H
#define STACK_H
#include "./structure.h"

typedef struct Stack
{
    int nbre_element;
    struct element *head;

}*Stack , Stack_element;



Stack new_stack(void);
boolean is_empty_stack(Stack stk);
void *pop(Stack stk);
void push(Stack stk , void *value);
void print_stack(Stack stk , void print_value(void *value));
void free_stack(Stack stk);

#endif
#ifndef STACK_C
#define STACK_C

#include "../header/stack.h"
#include <stdlib.h>
#include <stdio.h>

Stack new_stack(void){
    Stack pile = malloc(sizeof(Stack_element));
    pile->head = NULL;
    pile->nbre_element = 0;
    return pile;
}

boolean is_empty_stack(Stack stk){
    if(stk->head == NULL){
        return True;
    }else{
        return False;
    }
}

void *pop(Stack stk){
    typedef struct element element;
    if(is_empty_stack(stk) == True){
        return NULL;
    }else{
        element *head_element = stk->head;
        //on met a jour la nouvelle tete de la pile
        stk->head = stk->head->next;
        void *value = head_element->value;
        free(head_element);
        return value;
    }
}

void push(Stack stk, void *value){
    typedef struct element element;
    stk->nbre_element += 1;   
    if(is_empty_stack(stk) == True){
        element *elem = malloc(sizeof(element));
        elem->value = value;
        elem->next = NULL;
        stk->head = elem;
    }else{
        element *elem = malloc(sizeof(element));
        elem->value = value;
        elem->next = stk->head;
        stk->head = elem;
    }
}

void print_stack(Stack stk, void print_value(void *value)){
    typedef struct element element;
    element *head = stk->head; 
    while (head != NULL)
    {
        print_value(head->value);
        head = head->next;
    }
}

void free_stack(Stack stk){
    while (is_empty_stack(stk) == False)
    {
        pop(stk);
    }
    free(stk);
}

#endif 
#ifndef __STACK__
#define __STACK__

typedef struct Stack
{
    int count ;
    struct point *head ;
} Stack;
// x pour i et y pour j
typedef struct point
{
    int x, y;
    struct point *next ;
} point;

//permet d'initialiser la pile
Stack* initialize(void);
//permet d'ajouter un point dans la pile
void push(Stack *stack , int x , int y);
//permet d'extraire l'element en tete de pile
Stack* pop(Stack*);
//verifit si la pile est vide
int isEmpty(Stack*);
//afficher la pile
void print_stack(Stack*);

#endif
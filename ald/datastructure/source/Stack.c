#include <stdio.h>
#include <stdlib.h>

#include "../header/Stack.h"

Stack *initialize(void)
{
    Stack *p = (Stack *)malloc(sizeof(Stack));
    if (p == NULL)
    {
        printf("Impossible d'allouer l'espace memoire");
        exit(1);
    }
    printf("initialisation reussi\n");
    p->count = 0;
    p->head = NULL;
    return p;
}
void push(Stack *stack, int x, int y)
{
    point *p = (point *)malloc(sizeof(point));
    p->x = x;
    p->y = y;
    stack->count++ ;
    p->next = stack->head;
    stack->head = p;
}

Stack* pop(Stack* stack){
   point *p = stack->head ;
   stack->head = p->next;
   stack->count--;
   free(p);
   return stack;
}

int isEmpty(Stack* stack){
  if (stack->count != 0)
  {
      return 0;
  }else
  {
      return 1;
  }
  
  
}

void print_stack(Stack *stack)
{

    if (stack->count != 0)
    {
        point *p = stack->head;
        while (p != NULL)
        {
            printf("(%d ,%d ) \n", p->x, p->y);
            p = p->next;
        }
    }
    else
    {
        printf("Pile vide\n");
    }
}

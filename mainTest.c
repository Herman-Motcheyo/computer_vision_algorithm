#include <stdio.h>
#include "./Header/Stack.h"
int main(int argc, char const *argv[])
{
     Stack *s  = initialize();
     push(s , 10 ,15); 
      push(s , 8 ,1); 
       push(s ,0 ,5);
       push(s , 7 ,5); 
           print_stack(s);
     printf("les elements sont bien insere ");
    pop(s);
    pop(s);
    print_stack(s);
    printf("%d" , isEmpty(s));
    return 0;
}
#include "../Header/Convolution.h"

struct Image filter_with_median(struct Image img  , int rayon ){

}
struct Image filter_with_mean(struct Image img  , int rayon){
        int filtre[3][3] = {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}
    };
   int i=0 , j=0 , u=0 ,v=0 , sum=0;
   int **conv  = generate_matrice(img.largeur , img.hauteur);
   for ( i = 0; i < img.largeur; i++)
   {
       for ( j = 0; j < img.largeur; j++)
       {  sum  = 0;
           for (u = 0; u < i; u++)
           {
               for (v  = 0; v < j; v++)
               {
                   sum = sum + img.M[i-v][j-v]* filtre[u][v] ;
               }
               
           }
           conv[i][j] = sum;
           
       }
       
   }
   
}
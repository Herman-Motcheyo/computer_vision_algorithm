#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include  <math.h>

#include "../Header/Contour.h"


Image derive(Image m , int seuil){
    if (seuil < 1 || seuil  > m.MAX_PIXEL_VALUE-1 )
    {
        printf("Le seuil doit etre compris entre %d et %d " , seuil , m.MAX_PIXEL_VALUE);
        exit(1);
    }
    int** m_gradiant = generate_matrice(m.largeur, m.hauteur);
    int i=0,j=0;
    float norme = 0;
    for ( i = 0; i < m.largeur-1; i++)
    {
        for ( j = 0; j < m.hauteur-1; j++)
        {
            norme = sqrt( pow((m.M[i+1][j] - m.M[i][j]) ,2) + pow((m.M[i][j+1] - m.M[i][j]) ,2)  );
            if (norme > seuil)
            {
                m_gradiant[i][j] = norme;
            }
        }
        
    }
    m.M = m_gradiant;
    return m;
}

Image laplacien(Image m , int seuil){
   return derive(derive(m , seuil),seuil);
}

void contour(Image m, char* type , int seuil){
  if (strcmp(type , "sobel" )== 0)
  {
     Image m =  contour_filter("./filtre/sobel.txt" , m , seuil);
     if (m.M == NULL)
     {
         printf("erreur de l'operation");
     }else
     {
         write_Image_to_file(m , "sobel.pbm");
         printf("filtrage reussi avec sobel");
     }
     
     
  }
  
}

Image contour_with_sobel(Image m)
{
    float **sobel = initialise_filtre(1);
    sobel[0][0] = -1;
    sobel[0][1] = 0;
    sobel[0][2] = 1;
    sobel[1][0] = -2;
    sobel[1][1] = 0;
    sobel[1][2] = 2;
    sobel[2][0] = -1;
    sobel[2][1] = 0;
    sobel[2][2] = 1;

    m.M = convolveMult(m.M, sobel, m.largeur, m.hauteur, 1, m.MAX_PIXEL_VALUE);

    freeFilter(sobel , 3);
    return m;
}
Image contour_with_Prewitt(Image m ){

    float **Prewitt = initialise_filtre(1);
    Prewitt[0][0] = -1;
     Prewitt[0][1] = -1;
     Prewitt[0][2] = -1;
     Prewitt[1][0] = 0;
     Prewitt[1][1] = 0;
     Prewitt[1][2] = 0;
     Prewitt[2][0] = 1;
     Prewitt[2][1] = 1;
     Prewitt[2][2] = 1;


    m.M = convolveMult(m.M, Prewitt, m.largeur, m.hauteur, 1, m.MAX_PIXEL_VALUE);

    freeFilter(Prewitt , 3);

    return m;
}


Image contour_with_Roberts(Image m){
    float **roberts = initialise_filtre(1);
     float **roberts2 = initialise_filtre(1);
     roberts[0][0] = 1;
     roberts[0][1] = 0;
     roberts[1][0] = 0;
     roberts[1][1] = -1;

      roberts2[0][0] = 0;
     roberts2[0][1] = 1;
     roberts2[1][0] = -1;
     roberts2[1][1] = 0;


    m.M = convolveMult(m.M, roberts, m.largeur, m.hauteur, 1, m.MAX_PIXEL_VALUE);
    m.M = convolveMult(m.M, roberts2, m.largeur, m.hauteur, 1, m.MAX_PIXEL_VALUE);
    freeFilter(roberts , 3);
     freeFilter(roberts2 , 3);
    return m;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include  <math.h>

#include "../Header/Contour.h"

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
            }else{
                 m_gradiant[i][j] =0;
            }
            
        }
        
    }
    m.M = m_gradiant;
    return m;
}
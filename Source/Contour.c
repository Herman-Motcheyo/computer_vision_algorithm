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
    Image img = create_image(m);
  //  int** m_gradiant = generate_matrice(m.largeur, m.hauteur);
    int i=0,j=0;
    float norme = 0;
    for ( i = 0; i < m.largeur-1; i++)
    {
        for ( j = 0; j < m.hauteur-1; j++)
        {
            norme = sqrt( pow((m.M[i+1][j] - m.M[i][j]) ,2) + pow((m.M[i][j+1] - m.M[i][j]) ,2)  );
            if (norme > seuil)
            {
                img.M[i][j] = norme;
            }
        }
        
    }
   // m.M = m_gradiant;
    return img;
}
//2free à faire
Image laplacien(Image m , int seuil){
    Image im = create_image(m);
    im = derive(m,seuil);
   return derive(im,seuil);
}

void contour(Image m, char* type , int seuil){
  if (strcmp(type , "sobel" )== 0)
  {
     Image mp =  contour_filter("./filtre/sobel.txt" , m , seuil);
     if (mp.M == NULL)
     {
         printf("erreur de l'operation de detection decontour");
     }else
     {
         write_Image_to_file(mp , "./image/contour/filtrage_sobel.pbm");
         printf("OPeration de contour  reussi avec sobel");
     }
  }else {
         
     Image ms =  contour_filter("./filtre/prewitt.txt" , m , seuil);
     if (ms.M == NULL)
     {
         printf("erreur de l'operation de detection decontour");
     }else
     {
         write_Image_to_file(ms , "./image/contour/filtrage_prewitt.pbm");
         printf("OPeration de contour  reussi avec prewitt");
     }
     }    
  
}
// transformé de hougth pour la detection des lignes de manieres globales
// dans l'image
typedef struct Intensite
{
    int rho;
    int theta;
};

void hough(Image img , int theta , int rho , int seuil){
   int** houghTable = generate_matrice(rho , theta);
   Image result = create_image(img);
   int d = 0;
   for (int x = 0; x < img.largeur; x++)
   {
       for (int y = 0; y < img.hauteur ; y++)
       {
           for (int th  = 0; th < theta; th++)
           {
                d = x* cos(theta) - y*sin(theta); //on utilise les coordonnées polaires
                if (d >=0  )
                {
                    houghTable[d][th] = houghTable[d][th]+1 ; //l'accumulateur
                }
                
           }
           
       }
       //on recherche les valeurs de (rho , théta ) qui sont superieur au seuil
       for (size_t r = 0; r < rho; r++)
       {
           for (size_t th = 0; th < theta; th++)
           {
               if (houghTable[r][th] >= seuil)
               {
                 
               }
               
           }
           
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
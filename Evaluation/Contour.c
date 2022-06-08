#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include  <math.h>

#include "Contour.h"
#include "Stack.h"


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

Image gradiant(Image m , int seuil){
    if (seuil < 1 || seuil  > m.MAX_PIXEL_VALUE-1 )
    {
        printf("Le seuil doit etre compris entre %d et %d " , seuil , m.MAX_PIXEL_VALUE);
        exit(1);
    }
    Image img = create_image(m);
  //  int** m_gradiant = generate_matrice(m.largeur, m.hauteur);
    int i=0,j=0;
    float norme = 0;
    strcpy(m.name ,"P1");
    for ( i = 0; i < m.largeur-1; i++)
    {
        for ( j = 0; j < m.hauteur-1; j++)
        {
            norme = sqrt( pow((m.M[i+1][j] - m.M[i][j]) ,2) + pow((m.M[i][j+1] - m.M[i][j]) ,2)  );
            if (norme > seuil)
            {
                img.M[i][j] = 1;
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

int normalize( int value , int min , int max){
    int a = 255*(value - min)/(max- min) ;
    return a;
}

// transformé de hougth pour la detection des lignes de manieres globales
// dans l'image

/*
typedef struct Intensite
{
    int rho;
    int theta;
};


void hough(Image img , int theta_input , int seuil){
   int ny = img.largeur ;//nombre de pixels horizontale
   int nx = img.hauteur ;//nombre de pixels verticale
   // rho  en pixel et theta en degre sont les accumulateurs
   float rho = 1.0;
   float theta = 1.0;
   int n_theta = (int)(theta_input/theta); //n_theta nombre d'angles 
   int n_rho = (int)floor(sqrt(pow(nx ,2)+ pow(ny,2))/rho); //nombre de pixels
   float dtheta  = 3.14 * n_theta ;
   int dmax =  (int)floor(sqrt(pow(nx ,2)+ pow(ny,2))/rho); 
   int  d = (int)floor(sqrt(pow(nx ,2)+ pow(ny,2))/n_rho); // pour trouver d
   int** houghTable = generate_matrice(dmax*2 , n_theta);
   int** accumulateur2 = generate_matrice(n_theta , 2*dmax);
    double a ,b ;
   int x0,y0;
   printf("n_theta %d\n" ,n_theta);
   printf("n_rho %d\n" ,n_rho);
   printf("d %d\n" ,n_theta);
   Image result;
    result.M = generate_matrice(n_theta , n_rho);
   Stack *ligne = initialize() ;
   result.largeur = 2*dmax;
   result.hauteur = n_theta ;
   strcpy(result.name, "P1");
   strcpy(result.description , "# test");
   result.MAX_PIXEL_VALUE = 255;
   int i_d ,i_theta = 0;
   
      Image mp = gradiant(img , seuil);
   //  Image mp =  contour_filter("./filtre/sobel.txt" , img , seuil);
     if (mp.M == NULL)
     {
         printf("erreur de l'operation de detection decontour");
         exit(1);
     }

   for (int x = 0; x < mp.largeur; x++)
   {
       for (int y = 0; y < mp.hauteur ; y++)
       {  if (mp.M[x][y] != 0)
       {
            for (int th  = 0; th < n_theta; th++)
           {  
               // d = x* floor(cos((th/180))*3.14) + (y)*floor(sin((th/180))*3.14); //on utilise les coordonnées polaires
              // printf("%d , %d\n" , floor(cos(th/180)*3.14),floor(sin(th/180)*3.14 );
                if (dmax+ d  > 0 &&  dmax+ d < dmax )
                {
                    houghTable[d + dmax][th] ++ ; //l'accumulateur
                     printf("%d \n" , houghTable[d+dmax][th]);
                }
                
           }
       }   
       }
   }
int max = findMax(houghTable , 2*dmax , n_theta);
for (int i = 0; i <2*dmax; i++)
{
  for (int j = 0; j < n_theta; j++)
  {
      houghTable[i][j] = normalize(houghTable[i][j] , 0 ,max );
  }
  
}



       //on recherche les valeurs de (rho , théta ) qui sont superieur au seuil
    for (int r = 0; r <dmax*2 ; r++)
       {
           for (int th = 0; th <n_theta ; th++)
           {
               if (houghTable[r][th] >= seuil)
               {
              //    push(ligne ,r , (th/180)*3.14 );  
                //  accumulateur2[th][r] = 255;        
               }
               
           }
           
       }

        point *p = ligne->head;
        while (p != NULL)
        {   a = cos(p->y);
            b = sin(p->y);
            x0 =p->x+ p->x*a;
            y0 = p->x + p->x*b;
            if (x0 >=0 && y0>=0 && y0 < n_rho && x0 < n_theta )
            {
                accumulateur2[x0][y0] = 255;
            }
            
          //  accumulateur2[y0][x0] = 255;
        //   printf("(%d ,%d ) \n", x0, y0);
         p = p->next;
        }
       
    print_stack(ligne);
   result.M = houghTable ;
        write_Image_to_file(result , "hougth.pgm");
        write_Image_to_file_Pbm(mp , "bin.pbm");

}
*/
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Header/Operations.h"


/*
    this function is used to read and Image 
*/
struct Image read_Image_file(char *path)
{
    struct Image img;

    FILE *file = NULL;
    file = fopen(path, "r");
    int i = 0, j = 0;
    char name[20], description[200];
    if (file != NULL)
    {
        fgets(name, 20, file);
        strcpy(img.name, name);
        if (strcmp(img.name, "P2\n") == 0)
        {
            fgets(description, 200, file);
            strcpy(img.description, description);
            fscanf(file, "%d", &img.hauteur);
            fscanf(file, "%d", &img.largeur);
            fscanf(file, "%d", &img.MAX_PIXEL_VALUE);
            img.M = generate_matrice(img.largeur, img.hauteur);
            for (i = 0; i < img.largeur; i++)
            {
                for (j = 0; j < img.hauteur; j++)
                {
                    fscanf(file, "%d", &img.M[i][j]);
                }
            }
        }
        fclose(file);
        return img;
    }
    else
    {
        printf("impossible de lire le fichier de l'Image ou chemin incorrect");
        return img;
    }
}

/*
 this function is used to write an Image to file
*/
void write_Image_to_file(struct Image img, char *path)
{
    FILE *file_write = NULL;
    file_write = fopen(path, "w");
    int i, j = 0;
    if (file_write != NULL)
    {
        fprintf(file_write, "%s\n", img.name);
        fprintf(file_write, "%s\n", img.description);
        fprintf(file_write, "%d ", img.hauteur);
        fprintf(file_write, "%d\n", img.largeur);
        fprintf(file_write, "%d\n", img.MAX_PIXEL_VALUE);
        for (i = 0; i < img.largeur; i++)
        {
            for (j = 0; j < img.hauteur; j++)
            {
                fprintf(file_write, "%d\n", img.M[i][j]);
            }
        }

        fclose(file_write);
    }
    else
    {
        printf("erreur impossible d'ouvrir le fichier d'affichage de l'Image");
    }
}
/*
 * This function is used to transpose matrux
*/
struct Image transpose_Image(struct Image img)
{
    int i = 0, j = 0;
    Image m = create_image(img);
     m.M = generate_matrice(img.hauteur , img.largeur);

    for (i = 0; i < img.largeur; i++)
    {
        for (j = 0; j < img.hauteur; j++)
        {
             m.M[j][i] =  img.M[i][j];
        }
    }
    strcpy(m.description, "# transpose by herman");

    return m;
}   

/* Amelioration du constraste de l'Image */

/*
* this function is used to improve constrate of an Image using 
*   linear transformation
*/
struct Image transformation_lineaire(struct Image img)
{   
    int max = findMaxPixelValueInM(img);
    int min = findMinPixelValueInM(img);
    int i = 0, j = 0, tmp = 0;
    Image m = create_image(img) ;
     for (i = 0; i < img.largeur; i++)
    {
        for (j = 0; j < img.hauteur; j++)
        {
            tmp = img.M[i][j] - min;
            if (tmp < 0)
            {
                tmp = 0;
                m.M[i][j] = tmp;
            }
            else
            {
                m.M[i][j] = (tmp * 255) / (max - min);
            }
        }
    }
    strcpy(m.description, "# amelioration du constraste et transformation lineaire by herman");
    return m;
}


struct Image transformation_saturation(struct Image img, int smax, int smin)
{
       if (smax > findMaxPixelValueInM(img)  )
    {
        printf("la valeur maximale entree est tres superieur au pixel max qui est %d",findMaxPixelValueInM(img));
        exit(1);
    }
    else if (smin < findMinPixelValueInM(img) )
    {
        printf("La valeur min du pixel spécifie est inferieur à val min de l'image qui est %d" , findMinPixelValueInM(img));
        exit(1);
    }else if (smin > smax)
    {
        printf("Le max doit etre inferieur au min smax = %d smin= %d " ,smax , smin );
        exit(1);
    }
    int i=0 , j=0 , tmp=0;
  Image m = create_image(img) ;
    for (i = 0; i < img.largeur; i++)
    {
        for (j = 0; j < img.hauteur; j++)
        {
            tmp = img.M[i][j] - smin;
            if (tmp < 0)
            {
                tmp = 0;
                m.M[i][j] = tmp;
            }
            else
            {
                m.M[i][j] = (tmp * 255) / (smax - smin);
            }
        }
    }
    strcpy(m.description, "#  transformation lineaire avec saturation by herman");
    return m;
}
/*
* This function is used to improve contrast (à partir de l'etirement de l'histogramme)
*/
struct Image egalisation_histogramme(Image img){
   int i =0,j=0 ;
   float sum=0;
   float *H = calloc(img.MAX_PIXEL_VALUE , sizeof(float));
   float *C = calloc(img.MAX_PIXEL_VALUE ,  sizeof(float));
   Image m = create_image(img);
// Etape 1 : Calcul de l'histogramme
   for (i  = 0; i < img.largeur; i++)
   {
       for ( j = 0; j < img.hauteur; j++)
       {
           H[img.M[i][j]] += 1;
       }
       
   }
   //Etape 2 : Normalisation de l'histogramme
   for ( i = 0; i < img.MAX_PIXEL_VALUE; i++)
   {
       H[i] = H[i]/(img.largeur *img.hauteur) ;
   }
   
   // Etape 3 : Densité de probabilité normalisé
   for ( i = 0; i < img.MAX_PIXEL_VALUE; i++)
   {   
       for ( j = 0; j < i; j++)
       {
           sum += H[j];
       }
       C[i] = sum;
       sum = 0;
   }
   //Etape 4 : Transformation des niveaux de gris de l'image
   for ( i = 0; i < img.largeur; i++)
   {
       for (j = 0; j < img.hauteur; j++)
       {
           m.M[i][j] = C[img.M[i][j]] *img.MAX_PIXEL_VALUE;
       }
       
   }
   strcpy(m.description , "# Egalisation by tcheneghon Herman");
    return m;
}

int MAX_VALUE(int a ,int b){
    if (a<b )return b;
    else return a ;
}


int MIN_VALUE(int a ,int b){
    if (a<b )return a;
    else return b ;
}


struct Image addition(struct Image img1, struct Image img2)
{    
    if((img1.hauteur * img1.largeur) != (img2.hauteur * img2.largeur) ){
        printf("les 2 images doivent avoir la meme taille");
        exit(1);
    }
    int i = 0, j = 0;
    struct Image addition = create_image(img1);
    strcpy(addition.description , "# Herman Motcheyo addition");
    for (i = 0; i < img1.largeur; i++)
    {
        for ( j = 0; j < img1.hauteur; j++)
        {
            addition.M[i][j] = MIN_VALUE(img1.M[i][j]+ img2.M[i][j] , 255);
        }
        
    }
    return addition;
}


struct Image soustration(struct Image img1, struct Image img2)
{   if((img1.hauteur * img1.largeur) != (img2.hauteur * img2.largeur) ){
        printf("les 2 images doivent avoir la meme taille");
        exit(1);
    }
    int i = 0, j = 0;
    struct Image soustration  = create_image(img1);
   
    strcpy(soustration.description , "# Herman Motcheyo soustration");
    soustration.MAX_PIXEL_VALUE =255;
    for (i = 0; i < img1.largeur; i++)
    {
        for ( j = 0; j < img1.hauteur; j++)
        {
            soustration.M[i][j] = MAX_VALUE(img1.M[i][j]- img2.M[i][j] , 0);
        }
        
    }
    return soustration;
}

struct Image multiplication(struct Image img1, float ratio)
{
    int i = 0, j = 0;
    struct Image multiplication = create_image(img1);

    strcpy(multiplication.description , "# Herman Motcheyo multiplication");
    for (i = 0; i < img1.largeur; i++)
    {
        for ( j = 0; j < img1.hauteur; j++)
        {
            multiplication.M[i][j] = MAX_VALUE(img1.M[i][j]*ratio , 255);
        }
        
    }
    return multiplication;
}

struct Image binarisation(Image img , int seuil){

    
    int i =0 , j=0;
    Image m;
    m.hauteur= img.hauteur;
    m.largeur = img.largeur;
    m.M = generate_matrice(img.largeur , img.hauteur);
    for ( i = 0; i < img.largeur; i++)
    {
       for ( j = 0; j < img.hauteur; j++)
       {
           m.M[i][j] = (img.M[i][j]< seuil ) ? 0 : 1 ;

       }
       
    }
    strcpy(m.name ,"P1");

    return img;
    
}

//  negatif de l' image 255 -M[i][j]
struct Image negatif_image(struct Image img){
    int i = 0, j=0;
    struct Image m = create_image(img);
    strcpy(m.description , "# Herman Motcheyo negatif d'une image");
    for ( i = 0; i < img.largeur; i++)
    {
        for ( j = 0; j < img.hauteur; j++)
        {
            m.M[i][j] = 255 -img.M[i][j];
        }
        
    }
    return  m;
}

//la luminance est definie comme la moyenne de tous les pixels de l'image
struct Image luminanceImage(struct Image img){
   float moyenne = luminance(img);
   Image m = create_image(img);

   int i = 0,j=0;
   for ( i = 0; i < img.largeur; i++)
   {
       for ( j = 0; j < img.largeur; j++)
       {
           if (img.M[i][j] + moyenne  < img.MAX_PIXEL_VALUE )
           {
              m.M[i][j] = img.M[i][j]+moyenne; 
           }else{
               m.M[i][j] = img.M[i][j];
           }
           
       }
       
   }
   return m;
}


struct Image contrasteImage(struct Image img){
   float contrast = contraste(img);
   Image m = create_image(img);
   int i = 0,j=0;
   for ( i = 0; i < img.largeur; i++)
   {
       for ( j = 0; j < img.largeur; j++)
       {
           if (img.M[i][j] + contrast  < img.MAX_PIXEL_VALUE )
           {
              m.M[i][j] = img.M[i][j]+contrast; 
           }else{
               m.M[i][j] = img.M[i][j];
           }
           
       }
       
   }
   return m;
}

void histogramme(Image m){
 int *LUT = calloc(256 ,sizeof(int));
 int i =0 ,j=0;
 for ( i = 0; i < m.largeur; i++)
 {
     for ( j = 0; j < m.hauteur; j++)
     {
         LUT[m.M[i][j]]++;
     }
     
 }
 for (i = 0; i < 256; i++)
 {
     printf("%d \t" , LUT[i]);
 }
 write_Histogramme_to_File(LUT);
 free(LUT);
}

void write_Histogramme_to_File(int* hist){
    FILE *file = NULL;
    int i = 0;
    file = fopen("./image/cours/histogramme.txt" ,"a");
    if (file != NULL)
    {   fprintf(file ,"Numero  Count\n");
        for ( i = 0; i < 256; i++)
        {
            fprintf(file , "%d     %d\n" , i , hist[i]);
        }
        
    }else{
        printf("Impossible d'ouvrir le fichier pour l'ecriture de l'histogramme");
    }
}

int findMaxPixelValueInM(Image m){
    int max =0 ,i=0,j=0;
for ( i = 0; i < m.largeur; i++)
{
    for ( j = 0; j < m.hauteur; j++)
    {
        if (m.M[i][j] > max) max = m.M[i][j];
        
    }
    
}
return max;
}


int findMinPixelValueInM(Image m){
    int min =255 ,i=0,j=0;
for ( i = 0; i < m.largeur; i++)
{
    for ( j = 0; j < m.hauteur; j++)
    {
        if (m.M[i][j] < min) min = m.M[i][j];
        
    }
    
}
return min;
}

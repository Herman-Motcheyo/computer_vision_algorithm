#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "./Image.h"
/*    
**  this function is used to generate matrix 
*/

/// This function is using to create image

Image create_image(Image m){
    Image prime ;
    prime.hauteur = m.hauteur;
    prime.largeur = m.largeur;
    strcpy(prime.description , m.description);
    strcpy(prime.name , m.name);
    prime.MAX_PIXEL_VALUE = m.MAX_PIXEL_VALUE;
    prime.M = generate_matrice(m.largeur , m.hauteur);
    return prime;
}

int **generate_matrice(int nb_line, int nb_column)
{
    int i = 0;
    int **M = calloc(nb_line, sizeof(int *));
    for (i = 0; i < nb_line; i++)
    {
        M[i] = calloc(nb_column, sizeof(int));
    }
    return M;
}

void freeMatrice(int **m, int nb_line)
{
    int i =0;
    for ( i = 0; i < nb_line; i++){
        free(m[i]);
    }
    free(m);   
}

float luminance(Image m){
    float s = 0;
    int i =0 ,j=0;
    for ( i = 0; i < m.largeur; i++)
    {
        for (j  = 0;  j< m.hauteur; j++)
        {
            s += m.M[i][j];
        }
    }
    return s/ (m.hauteur *m.largeur);
}


Image seuillage_historgramme(const Image m){
    float T = luminance(m);
    Image seuille = create_image(m);
    strcpy(seuille.name ,  "P1");
    seuille.MAX_PIXEL_VALUE =1;
    for (int i = 0; i < seuille.largeur; i++)
    {
        for (int j = 0; j < seuille.hauteur; j++)
        {
            seuille.M[i][j] = (m.M[i][j] < T )? 1:0 ;
        }
        
    }
    return seuille;
}

float contraste(Image m){
  float moyenne  = luminance(m);
  int i=0 ,j = 0;
  float s=0;
  for ( i = 0; i < m.largeur; i++)
  {
      for ( j = 0; j < m.hauteur; j++)
      {
          s +=  pow(m.M[i][j]- moyenne , 2);
      }
      
  }
return sqrt(s/(m.hauteur * m.largeur));
}

Image read_pbm_file(char *path)
{

    struct Image img;

    FILE *file = NULL;
    file = fopen(path, "r");
    int i = 0, j = 0;
    char name[20], description[200];
    img.MAX_PIXEL_VALUE = 1;
    if (file != NULL)
    {
        fgets(name, 20, file);
        strcpy(img.name, name);
        if (strcmp(img.name, "P1\n") == 0)
        {
            printf("hello");
            // fgets(description, 200, file);
            strcpy(img.description, description);
            fscanf(file, "%d", &img.hauteur);
            fscanf(file, "%d", &img.largeur);
            img.M = generate_matrice(img.largeur, img.hauteur);
            for (i = 0; i < img.largeur; i++)
            {
                for (j = 0; j < img.hauteur; j++)
                { //  printf("%d" , fgetc(file));
                    //img.M[i][j] = fgetc(file);
                    fscanf(file, "%1d\n", &img.M[i][j]);
                    // printf("%d" ,img.M[i][j] );
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

void write_Image_to_file_Pbm(struct Image img, char *path)
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
        for (i = 0; i < img.largeur; i++)
        {
            for (j = 0; j < img.hauteur; j++)
            {
                fprintf(file_write, "%d", img.M[i][j]);
            }
        }

        fclose(file_write);
    }
    else
    {
        printf("erreur impossible d'ouvrir le fichier d'affichage de l'Image");
    }
}
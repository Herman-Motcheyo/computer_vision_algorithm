#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Header/Operations.h"

/*    
**  this function is used to generate matrix 
*/

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

/*
    this function is used to read and image 
*/
struct image read_image_file(char *path)
{
    struct image img;

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
        printf("impossible de lire le fichier de l'image ou chemin incorrect");
        return img;
    }
}

/*
 this function is used to write an image to file
*/
void write_image_to_file(struct image img, char *path)
{
    FILE *file_write = NULL;
    file_write = fopen(path, "a");
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
        printf("erreur impossible d'ouvrir le fichier d'affichage de l'image");
    }
}
/*
 * This function is used to transpose matrux
*/
struct image transpose_image(struct image img)
{
    int i = 0, j = 0;
    int tmp; 
     int **m_trans =m_trans= generate_matrice(img.hauteur, img.largeur);
    for (i = 0; i < img.largeur; i++)
    {
        for (j = 0; j < img.hauteur; j++)
        {
            m_trans[j][i] = img.M[i][j];
        }
    }
    img.M = m_trans;
    tmp=img.largeur ;
    img.largeur = img.hauteur;
    img.hauteur = tmp;
    strcpy(img.description , "# transpose by herman");

    return img ;
}


/* Amelioration du constraste de l'image */

/*
* this function is used to improve constrate of an image using 
*   linear transformation
*/
struct image transformation_lineaire( struct image  img, int max , int min){
    int i = 0, j=0 , tmp=0 ;
  int **m_prime = generate_matrice(img.largeur , img.hauteur);
  for (i = 0; i < img.largeur; i++)
    {
        for (j = 0; j < img.hauteur; j++)
        {   tmp = img.M[i][j] - min ;
            if (tmp < 0 )
            {
                tmp = 0;
                m_prime[i][j] = tmp;
            }else{
                m_prime[i][j] = (tmp *255) /(max -min);
            }
        }
    }
    strcpy(img.description ,"# amelioration du constraste et transformation lineaire by herman");
    img.M = m_prime;
    return img ;
}

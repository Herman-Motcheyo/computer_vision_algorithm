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
        printf("erreur impossible d'ouvrir le fichier d'affichage de l'Image");
    }
}
/*
 * This function is used to transpose matrux
*/
struct Image transpose_Image(struct Image img)
{
    int i = 0, j = 0;
    int tmp;
    int **m_trans = m_trans = generate_matrice(img.hauteur, img.largeur);
    for (i = 0; i < img.largeur; i++)
    {
        for (j = 0; j < img.hauteur; j++)
        {
            m_trans[j][i] = img.M[i][j];
        }
    }
    img.M = m_trans;
    tmp = img.largeur;
    img.largeur = img.hauteur;
    img.hauteur = tmp;
    strcpy(img.description, "# transpose by herman");

    return img;
}

/* Amelioration du constraste de l'Image */

/*
* this function is used to improve constrate of an Image using 
*   linear transformation
*/
struct Image transformation_lineaire(struct Image img, int max, int min)
{
    int i = 0, j = 0, tmp = 0;
    int **m_prime = generate_matrice(img.largeur, img.hauteur);
    for (i = 0; i < img.largeur; i++)
    {
        for (j = 0; j < img.hauteur; j++)
        {
            tmp = img.M[i][j] - min;
            if (tmp < 0)
            {
                tmp = 0;
                m_prime[i][j] = tmp;
            }
            else
            {
                m_prime[i][j] = (tmp * 255) / (max - min);
            }
        }
    }
    strcpy(img.description, "# amelioration du constraste et transformation lineaire by herman");
    img.M = m_prime;
    return img;
}

struct Image transformation_saturation(struct Image img, int max, int min, int smax, int smin)
{
  int i = 0, j = 0, tmp = 0;
    int **m_prime = generate_matrice(img.largeur, img.hauteur);
    for (i = 0; i < img.largeur; i++)
    {
        for (j = 0; j < img.hauteur; j++)
        {
            tmp = img.M[i][j] - smin;
            if (tmp < 0)
            {
                tmp = 0;
                m_prime[i][j] = tmp;
            }
            else
            {
                m_prime[i][j] = (tmp * 255) / (smax - smin);
            }
        }
    }
    strcpy(img.description, "# amelioration du constraste et transformation lineaire by herman");
    img.M = m_prime;
    return img;

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
    int i = 0, j = 0;
    struct Image addition;
    addition.hauteur= img1.hauteur;
    addition.largeur = img1.largeur;
    strcpy(addition.name , img1.name);
    strcpy(addition.description , "# Herman Motcheyo addition");
    addition.MAX_PIXEL_VALUE =255;

    addition.M = generate_matrice(img1.largeur , img1.hauteur);

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
{
    int i = 0, j = 0;
    struct Image soustration;
    soustration.hauteur= img1.hauteur;
    soustration.largeur = img1.largeur;
    strcpy(soustration.name , img1.name);
    strcpy(soustration.description , "# Herman Motcheyo addition");
    soustration.MAX_PIXEL_VALUE =255;

    soustration.M = generate_matrice(img1.largeur , img1.hauteur);

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
    struct Image multiplication;
    multiplication.hauteur= img1.hauteur;
    multiplication.largeur = img1.largeur;
    strcpy(multiplication.name , img1.name);
    strcpy(multiplication.description , "# Herman Motcheyo multiplication");
    multiplication.MAX_PIXEL_VALUE =255;

    multiplication.M = generate_matrice(img1.largeur , img1.hauteur);

    for (i = 0; i < img1.largeur; i++)
    {
        for ( j = 0; j < img1.hauteur; j++)
        {
            multiplication.M[i][j] = MAX_VALUE(img1.M[i][j]*ratio , 255);
        }
        
    }
    return multiplication;
}

struct Image Et(Image img1 , Image img2){

}
struct Image OU(Image img1 , Image img2){

}
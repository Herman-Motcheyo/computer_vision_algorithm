#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../Header/Convolution.h"

//(2*n + 1)* (2*n +1)
//Initialisation du filtre de l'image
float **initialise_filtre(int n)
{
    int i = 0;
    float **filtre = calloc((n * 2 + 1), sizeof(int *));
    for (i = 0; i < 2 * n + 1; i++)
    {
        filtre[i] = calloc((2 * n + 1), sizeof(int));
    }
    return filtre;
}

float **filtre_gaussien(int rayon){
    float** initialise_filtre(rayon);
    int i = 0, j = 0 , n =2 * rayon + 1 ;
}

float** filtre_moyenneur(int rayon)
{
    float** moyenneur = initialise_filtre(rayon);
    int i = 0, j = 0 , n =2 * rayon + 1 ;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
         {
                moyenneur[i][j] = 1;
         }

    }

    return moyenneur;
}
Image convolution(Image img, char *nom_filtre, int rayon)
{

    if (strcmp(nom_filtre, "moyenneur") == 0)
    {
        int total = (2 * rayon + 1) * (2 * rayon + 1);
        int n = 2 * rayon + 1;
         printf("Le Filtre est de taille  %d * %d", n , n);
        float **filtre = filtre_moyenneur(rayon);
        int i = 0, j = 0, u = 0, v = 0;
        for (i = 0; i < n; i++)
        {
            printf("\n");
            for (j = 0; j < n; j++)
            {
                printf("%f\t", filtre[i][j]);
            }
        }

        double s = 0, p = 0;
        int** conv = generate_matrice(img.largeur, img.hauteur);
        for (i = 0; i < img.largeur - 1; i++)
        {
            for (j = 0; j < img.hauteur - 1; j++)
            {
                s = 0;
                for (u = 0; u < n; u++)
                {
                    for (v = 0; v < n; v++)
                    {
                        if ((i + u - rayon) > 0 && (j + v - rayon) > 0 && (i + u - rayon < img.largeur) && (j + u - rayon < img.hauteur))
                        {
                            s += img.M[i + u - rayon][j + v - rayon] * filtre[u][v];
                        }
                    }
                }
                p = s / total;
                if (p < 0)
                {
                    conv[i][j] = 0;
                }
                else if (p > img.MAX_PIXEL_VALUE)
                {
                    conv[i][j] = 255;
                }
                else
                {
                    conv[i][j] = p;
                }
            }
        }
        img.M = conv;
        // freeMatrice(conv , img.largeur);
        return img;
    }
    else
    {
        printf("pas encore pret");
    }
}

struct Image filter_with_median(struct Image img, int rayon)
{
}
struct Image filter_with_mean(struct Image img, int rayon)
{
    /*float filtre[3][3] = {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}}; */
    float filtre[3][3] = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}};

    int i = 0, j = 0, u = 0, v = 0;
    double s = 0;
    int **conv = generate_matrice(img.largeur, img.hauteur);
    for (i = 0; i < img.largeur - 1; i++)
    {
        for (j = 0; j < img.hauteur - 1; j++)
        {
            s = 0;
            for (u = 0; u < 3; u++)
            {
                for (v = 0; v < 3; v++)
                {
                    if ((i + u) > 0 && (j + v) > 0)
                    {
                        s += img.M[i + u - 1][j + v - 1] * filtre[u][v];
                    }
                }
            }
            conv[i][j] = s / 9;
            if (conv[i][j] < 0)
            {
                conv[i][j] = 0;
            }
            else if (conv[i][j] > 255)
            {
                conv[i][j] = 255;
            }
        }
    }
    img.M = conv;
    // freeMatrice(conv , img.largeur);
    return img;
}
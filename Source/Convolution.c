#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Header/Convolution.h"

//(2*n + 1)* (2*n +1)
//Initialisation du filtre de l'image
int **initialise_filtre(int n)
{
    int i = 0;
    int **filtre = calloc((n * 2 + 1), sizeof(int *));
    for (i = 0; i < 2 * n + 1; i++)
    {
        filtre[i] = calloc((2 * n + 1), sizeof(int));
    }
    return filtre;
}

float **filtre_gaussien(int rayon);

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
    return img;
}
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

float **filtre_gaussien(int rayon, float ecart_type)
{
    float **gaussien = initialise_filtre(rayon);
    int i = 0, j = 0, n = 2 * rayon + 1;
    float sum = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            gaussien[i][j] = exp(-((pow(i, 2) + pow(j, 2)) / (2 * pow(ecart_type, 2))));
            sum += gaussien[i][j];
        }
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            gaussien[i][j] = gaussien[i][j] / sum;
        }
    }
    return gaussien;
}

float **filtre_moyenneur(int rayon)
{
    float **moyenneur = initialise_filtre(rayon);
    int i = 0, j = 0, n = 2 * rayon + 1;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            moyenneur[i][j] = 1;
        }
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            moyenneur[i][j] = moyenneur[i][j] / (n * n);     
        }
    }

    return moyenneur;
}
int**  convolveMult(int** m , float **filtre ,int largeur , int hauteur , int rayon , int MAX_PIXEL_VALUE){
       int i = 0, j = 0, u = 0, v = 0;
       int n = 2 * rayon + 1;
      double s = 0;
        int **conv = generate_matrice(largeur, hauteur);
        for (i = 0; i < largeur - 1; i++)
        {
            for (j = 0; j < hauteur - 1; j++)
            {
                s = 0;
                for (u = 0; u < n; u++)
                {
                    for (v = 0; v < n; v++)
                    {
                        if ((i + u - rayon) > 0 && (j + v - rayon) > 0 && (i + u - rayon <largeur) && (j + u - rayon < hauteur))
                        {
                            s += m[i + u - rayon][j + v - rayon] * filtre[u][v];
                        }
                    }
                }
                if (s < 0)
                {
                    conv[i][j] = 0;
                }
                else if (s >MAX_PIXEL_VALUE)
                {
                    conv[i][j] = 255;
                }
                else
                {
                    conv[i][j] = s;
                }
            }
        }
        // freeMatrice(conv , img.largeur);
        return conv;
}

Image convolution(Image img, char *nom_filtre, int rayon)
{
    if (strcmp(nom_filtre, "moyenneur") == 0)
    {   float **filtre = filtre_gaussien(rayon, contraste(img));
        int **conv = convolveMult(img.M , filtre,img.largeur ,img.hauteur , rayon , img.MAX_PIXEL_VALUE);
        img.M = conv;
        // freeMatrice(conv , img.largeur);
        return img;
    }
    else if (strcmp(nom_filtre, "gaussien") == 0)
    {
        float **filtre = filtre_gaussien(rayon, contraste(img));
        printFilter(filtre , rayon);
        int **conv = convolveMult(img.M , filtre,img.largeur ,img.hauteur , rayon , img.MAX_PIXEL_VALUE);
        img.M = conv;
        // freeMatrice(conv , img.largeur);
        return img;
    }
}

void printFilter(float** filtre , int rayon){
        int n = 2 * rayon + 1;
        int i = 0 , j=0;
       printf("Le Filtre est de taille  %d * %d", n, n);
        for (i = 0; i < n; i++)
        {
            printf("\n");
            for (j = 0; j < n; j++)
            {
                printf("%f\t", filtre[i][j]);
            }
        }
}


int findMedianWithBubbleSort(int* tab, int length){
    int  i=0,j=0,tmp=0; 
    for ( i = 0; i < length-1; i++)
    {   
        for ( j = 0; j < length-1; j++)
        {
            if (tab[j+1] < tab[j])
            {
                tmp = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = tmp;
            }   
        }

    }
    if (length % 2 != 0)
    { 
        tmp = tab[((length+1)/2)-1];
    }else
    {
        tmp  = ((tab[((length/2)+1)-1] + tab[(length/2)-1]))/2 ;
    }
    return tmp;
    
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
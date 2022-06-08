#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Convolution.h"

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
int **convolveMult(int **m, float **filtre, int largeur, int hauteur, int rayon, int MAX_PIXEL_VALUE)
{
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
                    if ((i + u - rayon) > 0 && (j + v - rayon) > 0 && (i + u - rayon < largeur) && (j + u - rayon < hauteur))
                    {
                        s += m[i + u - rayon][j + v - rayon] * filtre[u][v];
                    }
                }
            }
            if (s < 0)
            {
                conv[i][j] = 0;
            }
            else if (s > MAX_PIXEL_VALUE)
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
    Image m = create_image(img);
    if (strcmp(nom_filtre, "moyenneur") == 0)
    {
        float **filtre = filtre_gaussien(rayon, contraste(img));
        m.M = convolveMult(img.M, filtre, img.largeur, img.hauteur, rayon, img.MAX_PIXEL_VALUE);
        freeFilter(filtre , 2*rayon +1);
        // freeMatrice(conv , img.largeur);
        return m;
    }
    else if (strcmp(nom_filtre, "gaussien") == 0)
    {
        float **filtre = filtre_gaussien(rayon, contraste(img));
        printFilter(filtre, rayon);
        m.M = convolveMult(img.M, filtre, img.largeur, img.hauteur, rayon, img.MAX_PIXEL_VALUE);
        freeFilter(filtre , 2*rayon +1);
        // freeMatrice(conv , img.largeur);
        return m;
    }
    else
    {
        printf("Puisque le nom du filtre ne correspond a aucun nom , \n par defaut le median est applique\n");
        return filter_with_median(img, rayon);
    }
}

void printFilter(float **filtre, int rayon)
{
    int n = 2 * rayon + 1;
    int i = 0, j = 0;
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

int findMedianWithBubbleSort(int *tab, int length)
{
    int i = 0, j = 0, tmp = 0;
    for (i = 0; i < length - 1; i++)
    {
        for (j = 0; j < length - 1; j++)
        {
            if (tab[j + 1] < tab[j])
            {
                tmp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = tmp;
            }
        }
    }
    if (length % 2 != 0)
    {
        tmp = tab[((length + 1) / 2) - 1];
    }
    else
    {
        tmp = ((tab[((length / 2) + 1) - 1] + tab[(length / 2) - 1])) / 2;
    }
    return tmp;
}

struct Image filter_with_median(struct Image img, int rayon)
{
    int i = 0, j = 0, u = 0, v = 0;
    int n = 2 * rayon + 1;
    int *tab = calloc(n * n, sizeof(n * n));
    int s = 0;
    Image m = create_image(img);
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
                        tab[s] = img.M[i + u - rayon][j + v - rayon];
                        s += 1;
                    }
                }
            }
            m.M[i][j] = findMedianWithBubbleSort(tab, n * n);
        }
    }
    free(tab);
    return m;
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

void freeFilter(float **m, int n)
{
    int i = 0;
    for (i = 0; i < n; i++)
    {
        free(m[i]);
    }
    free(m);
}

float **read_filter(char *path)
{
    FILE *file = NULL;
    int rayon = 0;
    file = fopen(path, "r");
    float **filtre = NULL;
    if (file != NULL)
    {
        fscanf(file, "%d", &rayon);
        if (rayon >  0)
        {
            filtre = initialise_filtre(rayon);
            for (int i = 0; i < (2 * rayon + 1); i++)
            {
                for (int j = 0; j < (2 * rayon + 1); j++)
                {
                    fscanf(file, "%f", &filtre[i][j]);
                }
            }
            printFilter(filtre, rayon);
            return filtre;
        }else
        {
            printf("Le rayon doit etre strictement positif");
            return filtre;
        }
        
    }
    else
    {
        printf("Impossible  de lire le fichier . Probleme de chemin");
    }
    return filtre;
}

Image contour_filter(char *path, Image m, int seuil)
{
    FILE *file = NULL;
    int rayon = 0;
    file = fopen(path, "r");
    float **sx = NULL;
    float **sy = NULL;
    int amplitude = 0;
    Image spec ;
    strcpy(spec.name ,"P1");
    strcpy(spec.description , "# filtrage avec un filtre derivateur");
    spec.largeur = m.largeur;
    spec.hauteur = m.hauteur;
    spec.M = NULL;
    if (file != NULL)
    {
        fscanf(file, "%d", &rayon);
        if (rayon >  0)
        {
            sx = initialise_filtre(rayon);
            sy = initialise_filtre(rayon);
            for (int i = 0; i < (2 * rayon + 1); i++)
            {
                for (int j = 0; j < (2 * rayon + 1); j++)
                {
                    fscanf(file, "%f", &sx[i][j]);
                }
            }
            for (int i = 0; i < (2 * rayon + 1); i++)
            {
                for (int j = 0; j < (2 * rayon + 1); j++)
                {
                    fscanf(file, "%f", &sy[i][j]);
                }
            }
            spec.M = generate_matrice(m.largeur, m.hauteur);
            int **mx = convolveMult(m.M, sx, m.largeur, m.hauteur, rayon, m.MAX_PIXEL_VALUE);
            int **my = convolveMult(m.M, sy, m.largeur, m.hauteur, rayon, m.MAX_PIXEL_VALUE);
            for (int i = 0; i < m.largeur; i++)
            {
                for (int j = 0; j < m.hauteur; j++)
                {
                    amplitude = sqrt(pow(mx[i][j], 2) + pow(my[i][j], 2));
                    if (amplitude > seuil)
                    {
                        spec.M[i][j] = 0;
                    }else
                    {
                        spec.M[i][j] = 1;
                    }
                    
                }
            }
           
        //    printFilter(sy, rayon);
        freeMatrice(mx , spec.largeur);
        freeMatrice(my , spec.largeur);
        freeFilter(sx , 2*rayon +1);
        freeFilter(sy , 2*rayon +1);
            return spec;
        }else
        {
            printf(" le Rayon du filtre doit strictement etre positif");
            return spec;
        }
        
    }
    else
    {
        printf("Impossible  de lire le fichier . Probleme de chemin \n");
    }
    return spec;
}
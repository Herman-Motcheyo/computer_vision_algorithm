#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../Header/Segmentation.h"

int Manathan(int *tab, int *T, int n, int p)
{
    int value = 0;
    for (int i = 0; i < n; i++)
    {
        value += pow(tab[i] - T[i], p);
    }
    return pow(value, (1 / p));
}

void kmeans(Image img, int k, int min_inertia, int iter)
{

    Image m = create_image(img);
    if (k <= 0)
    {
        printf("le nombre de cluster est un entier strictement positif");
        exit(1);
    }
    else if (k == 1)
    {
        printf("Le nombre de cluster est à 1 Donc pas de modication");
        return m;
    }
    int n = m.largeur, index = 0;
    int **cluster = generate_matrice(k, n);
    double dist = 0;
    double dismin = 0;
    for (int p = 0; p < iter; p++)
    {

        for (int i = 0; i < n; i++)
        {
            dismin = INFINITY;
            for (int j = 0; j < k; j++)
            {
                dist = Manathan(m.M[i], cluster[j], n, 2);
                if (dist < dismin)
                {
                    dismin = dist;
                    index = j;
                }
            }
        }
    }
}
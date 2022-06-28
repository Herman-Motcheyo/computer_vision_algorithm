#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.141592

#include "../Header/Transformer_fourier.h"

int **M_Imaginaire(Image m)
{
    int **im = generate_matrice(m.largeur, m.hauteur);
    for (int i = 0; i < m.largeur; i++)
        for (int j = 0; j < m.hauteur; j++)
            for (int u = 0; u < m.largeur; u++)
                for (int v = 0; i < m.hauteur; v++)
                    im[i][j] = m.M[i][j] * sin(PI * 2 * ((i / m.largeur) + (j / m.hauteur)));

    return im;
}

Image norme_f(int **imR, int **imI, int largeur, int hauteur)
{
    int **spectre = generate_matrice(largeur, hauteur);

    for (int i = 0; i < largeur; i++)
    {
        for (int j = 0; j < hauteur; j++)
        {
            spectre[i][j] = sqrt(pow(imR[i][j], 2) + pow(imI[i][j], 2));
        }
    }
    Image m;
    m.MAX_PIXEL_VALUE = 255;
    m.hauteur = hauteur;
    m.largeur = largeur;
    m.M = spectre;
    strcpy(m.description, "# dfdfdf");
    strcpy(m.name, "P2");
    return m;
}

Image phase(int **imR, int **imI, int largeur, int hauteur)
{
    int **phasef = generate_matrice(largeur, hauteur);
    for (int i = 0; i < largeur; i++)
    {
        for (int j = 0; j < hauteur; j++)
        {
            if (imI[i][j] != 0 || imI[i][j] != 0)
            {
               // phasef[i][j] = 255;
              //  printf("%d \n", phasef[i][j]);
            }
            else
            {
                phasef[i][j] = 0;
            }
        }
    }
    Image m;
    m.MAX_PIXEL_VALUE = 255;
    m.hauteur = hauteur;
    m.largeur = largeur;
    m.M = phasef;
    strcpy(m.description, "# dfdfdf");
    strcpy(m.name, "P2");
    return m;
}
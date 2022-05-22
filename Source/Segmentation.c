#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../Header/Segmentation.h"

//permet de faire la distance entre le centroid et l'observation
int Manathan(int *tab, int *T, int n, int p)
{
    int value = 0;
    for (int i = 0; i < n; i++)
    {
        value += pow(tab[i] - T[i], p);
    }
    return pow(value, (1 / p));
}
//permet de faire la mise à jour d'un cluster
float *update_cluster(int **data, int n, int nbcolumn)
{
    float *newCluster = calloc(n, sizeof(int));
    float summ = 0;
    for (int i = 0; i < n; i++)
    {
        summ = 0;
        for (int j = 0; j < nbcolumn; j++)
        {
            summ += data[j][i];
        }
        summ /= n;
        newCluster[i] = summ;
    }
    return newCluster;
}
//permet de calculer le nombre d'elements qu'un cluster contient
int length_cluster(int *points, int clusterId, int length_point)
{
    int cpt = 0;
    for (int i = 0; i < length_point; i++)
        if (points[i] == clusterId)
            cpt++;
    return cpt;
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
    int **cluster = generate_matrice(k , m.hauteur);
    int *points = calloc(n, sizeof(int));
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
            points[i] = index;
        }
        int ind = 0;
        //update center
//idée de cette partie 
/*
pour mettre à jour le cluster , 
premierement je calcule son nbre d'elements
puisque ce sont les indices que je manipule , je crai une matrice qui contient la donnée
relative à chaque cluster . A partir de cette matrice ,je mets à jour le cluster avec le calcul
du centre de gravité. 
*/

        int **elment_in_cluster;
        for (int i = 0; i < k; i++)
        {
            ind = length_cluster(points, i, n);
            if (ind != 0)
            {
                elment_in_cluster = generate_matrice(ind, m.hauteur);
                for (int j = 0; j < n; j++)
                {
                    if (i == points[j])
                    {
                        elment_in_cluster[j] = m.M[j];
                    }
                }
                cluster[i]  = update_cluster(elment_in_cluster ,ind ,m.hauteur);
            }
        }
    }
}
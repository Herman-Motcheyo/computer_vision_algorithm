#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "../Header/Segmentation.h"

//permet de faire la distance entre le centroid et l'observation
int Manathan(int *tab, int *T, int n, int p)
{   int value = 0;
    for (int i = 0; i < n; i++)
    {
 
        value += pow(tab[i] - T[i], p);
    }
    return pow(value, (1 / p));
}

double distance(int *tab, float *T, int n)
{
    double value = 0;
    for (int i = 0; i < n; i++)
    {
        value +=tab[i] +T[i];
    }
    return sqrt(value);
}
//permet de faire la mise à jour d'un cluster
float *update_cluster(int **data, int n, int nbcolumn ,float * cluster)
{
    float *newCluster = calloc(n, sizeof(int));
    float summ = 0;
    for (int i = 0; i < n; i++)
    {
        summ = 0;
        for (int j = 0; j < nbcolumn; j++)
        {
            summ += data[i][j];
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
float **initialize_cluster(Image m, int k)
{
    float **cluster =calloc(m.largeur , sizeof(int*));
    for (int i = 0; i < m.largeur; i++)
    {
        cluster[i] = calloc(k, sizeof(float));
    }
     
    __time_t t;
    srand((unsigned)time(&t));
    for (int i = 0; i < k; i++)
    {
        cluster[i] = int_to_float( m.M[rand() % k] ,k);
     //   printf("%d\n", rand() % (m.largeur - 1));
    }
    return cluster;
}

float* int_to_float(int* t , int k){
    float *ret = calloc(k , sizeof(float));
    for (int i = 0; i < k; i++)
    {
        ret[i] = (float)t[i];
    }
    return ret ;
}
void kmeans(Image img, int k, int min_inertia, int iter)
{

    Image m = create_image(img);
    for (int i = 0; i < m.largeur; i++)
        for (int j = 0; j < m.largeur; j++)
            m.M[i][j] = img.M[i][j];

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
    float **cluster = initialize_cluster(m, k);
    int* points = calloc(n , sizeof(int));
    double dist = 0;
    double dismin = 0;
    int theta = 0;
    //printf("%f", distance(cluster[0], m.M[0], n));
    for (int p = 0; p < iter; p++)
    {

        for (int i = 0; i < n; i++)
        {
            dismin = INFINITY;
            for (int j = 0; j < k; j++)
            {
                dist = distance(m.M[i], cluster[j], n);
              
                if (dist <= dismin)
                {
                    dismin = dist;
                    //printf("%f\t",dismin);
                    index = j;
                  //  printf("%d\t", j);
                }
            }
           //printf("%d\t" , index);
            points[i] = index;
        }
        int ind =    0;

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
            {    theta = 0;
                elment_in_cluster = generate_matrice(ind, m.hauteur);
                for (int j = 0; j < n; j++)
                {
                    if (theta < ind)
                    {
                        if (i == points[j])
                        {
                            elment_in_cluster[theta] = m.M[j];
                            theta += 1;
                        }
                    }
                }

                cluster[i] = update_cluster(elment_in_cluster, ind, m.hauteur ,cluster[i]);
            }
        }
        
    }
for (int i = 0; i < n; i++)
{
        printf("%d\t" , points[i]);
}


}
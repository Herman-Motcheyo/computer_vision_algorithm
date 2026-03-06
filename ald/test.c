#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "./Header/Contour.h"
#include "./Header/Segmentation.h"


Image kmt(Image m, int K)
{
    int *nb_elements =calloc(K,sizeof(int));   //pour compteur le nombre d elements par cluster
    double *centre_cluster =calloc(K,sizeof(double));
    Image result = create_image(m);
    result.M = generate_matrice(m.largeur ,m.hauteur);
    double ini = 0;

    double *centre_aux_c = calloc(K,sizeof(double));
    int i, j, k, kmin, niter = 0;
    double vmin, aux;

    srand(time(NULL));
    printf("------Initialisation des centres-------------------\n");
    for (k = 0; k < K; k++)
    {
        ini = rand() / (RAND_MAX + 1.0);
        centre_cluster[k] = 255 * ini;//initialisation des centres finaux
        printf(" centre %d  valeur %d \n" , k , (int)centre_cluster[k]);
    }

    do
    {
        for (k = 0; k < K; k++)
        {
            nb_elements[k] = 0;
            centre_aux_c[k] = 0;
        }
        for (i = 0; i < m.largeur; i++)
        {
            for (j = 0; j < m.hauteur; j++)
            {
                kmin = 0;
                vmin = fabs(m.M[i][j] - centre_cluster[kmin]);
                for (k = 1; k < K; k++)
                {
                    aux = fabs(m.M[i][j] - centre_cluster[k]);
                    if (vmin > aux)
                    {
                        kmin = k;
                        vmin = aux;
                    }
                }
                result.M[i][j] = kmin;
                nb_elements[kmin]++;
                centre_aux_c[kmin] += m.M[i][j];
            }
        }
//mise à jour des centres
        for (k = 0; k < K; k++)
        {
            centre_aux_c[k] /= nb_elements[k];
            centre_cluster[k] = centre_aux_c[k];
        }
        niter++;
    } while ( 2000 > niter);
    for (i = 0; i < m.largeur; i++)
        for (j = 0; j < m.hauteur; j++)
            result.M[i][j] = centre_cluster[result.M[i][j]];
    return result;
}


int main(int argc, char const *argv[])
{
    Image m = read_Image_file("image/imgsource/original/radio.pgm");
    Image b ;
   //  b.M = kmf(m.M , m.largeur , m.hauteur , 2 ,0,255 , 0.201, 125544) ;
  //  Image k = kmeansfinale(m, 5, 1000);
    b = kmt(m , 3 ) ;
    write_Image_to_file(b , "kmean.pgm");
    return 0;
}





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "../Header/Segmentation.h"
#include "../Header/Operations.h"
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

double distance(int *tab, float *T, int n)
{
    double value = 0;
    for (int i = 0; i < n; i++)
    {
        value += tab[i] + T[i];
    }
    return sqrt(value);
}
//permet de faire la mise à jour d'un cluster
float *update_cluster(int **data, int n, int nbcolumn, float *cluster)
{
    float *newCluster = calloc(n, sizeof(int));
    float sommem = 0;
    for (int i = 0; i < n; i++)
    {
        sommem = 0;
        for (int j = 0; j < nbcolumn; j++)
        {
            sommem += data[i][j];
        }
        sommem /= n;
        newCluster[i] = sommem;
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
    float **cluster = calloc(m.largeur, sizeof(int *));
    for (int i = 0; i < m.largeur; i++)
    {
        cluster[i] = calloc(k, sizeof(float));
    }

    __time_t t;
    srand((unsigned)time(&t));
    for (int i = 0; i < k; i++)
    {
        cluster[i] = int_to_float(m.M[rand() % k], k);
        //   printf("%d\n", rand() % (m.largeur - 1));
    }
    return cluster;
}

float *int_to_float(int *t, int k)
{
    float *ret = calloc(k, sizeof(float));
    for (int i = 0; i < k; i++)
    {
        ret[i] = (float)t[i];
    }
    return ret;
}
void kmoyens(Image img, int k, int min_inertia, int iter)
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
    int *points = calloc(n, sizeof(int));
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
                theta = 0;
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

                cluster[i] = update_cluster(elment_in_cluster, ind, m.hauteur, cluster[i]);
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d\t", points[i]);
    }
}

int otsu_version_du_support_du_cours(int *hist, int largeur, int hauteur)
{
    double u1 = 0, u2 = 0, variance1 = 0, variance2 = 0, P1 = 0, P2 = 0;
    double variance_intraclasse = INFINITY;
    int seuil = 0;
    double *v = calloc(254, sizeof(double));
    int varmin = v[1];
    double somme1 = 0, somme2 = 0;

    for (int T = 1; T <= 255; T++)
    { //calcul de la moyenne U1
        for (int i = 0; i < T; i++)
        {
            u1 += hist[i];
            somme1 += hist[i];
        }
        u1 = u1 / T;
        //calcul de la moyenne U2
        for (int i = T; i < 255; i++)
        {
            u2 += hist[i];
            somme2 += hist[i];
        }
        u2 /= (256 - T);
        //calcul de la variance v1
        for (int i = 0; i < T; i++)
        {
            variance1 += pow((hist[i] - u1), 2);
        }
        variance1 /= T;
        //calcul de la variance v2
        for (int i = T; i < 255; i++)
        {
            variance1 += pow((hist[i] - u2), 2);
        }
        variance2 = variance2 / (256 - T);
        //calcul de la distribution de proba
        for (int i = 0; i < T; i++)
        {
            P1 += hist[i];
        }
        P1 = P1 / (largeur * hauteur);
        for (int i = T; i < 255; i++)
        {
            P2 += hist[i];
        }
        P2 = P2 / (largeur * hauteur);
        variance_intraclasse = P1 * variance1 + P2 * variance2;
        //      printf("le seuil min est , %f\n" , variance_intraclasse);
        v[T] = variance_intraclasse;
    }
    //recherche de la variance intraclasse miniminal et du seuil

    for (int i = 2; i < 254; i++)
    {
        if (varmin < v[i])
        {
            seuil = i;
            varmin = v[i];
        }
    }
    //   free(v);
    printf("le seuil est ,%d", seuil);
    return seuil;
    //    printf("le seuil est ,%d" , seuil);
}

Image seuillageAutomatique(Image img)
{
    int seuil = otsu(img.largeur, img.hauteur , img);
    printf("\n\t La valeur optimale du seuil  est %d \n", seuil);
Image m2 = binarisation(img, seuil);
    return m2;
}
//https://pdf.sciencedirectassets.com/270704/1-s2.0-S1110016820X00081/1-s2.0-S1110016820303215/main.pdf?X-Amz-Security-Token=IQoJb3JpZ2luX2VjEI3%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLWVhc3QtMSJIMEYCIQC0BN7CijSJw7HsIGKvQupRQe7K0dwIzEbs7KFvg546GgIhALmQDgG352u7vEitZj5J9La%2FOfdsFDGBVNBhLB6%2B34%2BzKtsECJb%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEQBBoMMDU5MDAzNTQ2ODY1IgxBIMKIo8azOzPO2c0qrwTRlYcyAVEJIGqKcfOoapFXL7JYj7EfBiex3cvVnsB8BVnOXpXIeKvwpVeV4G5dxM66IoiHIWxm9oOrAoc%2BBD1VqFwS0r4gQo%2FgLYR7TeMxDMxNcpjXZE%2BfkheO5VsIL89ZOGHfKYuj0hNYCIbyNkuFIq7PXspNyukE74XKuY%2FBXQCx%2FMyzS3brgOSgm9AZKBNAEbQBWGcgZxawfDsrrLNJbZLUauqN9OdHGIt8HJNZ077R3Ii8Kp85I86%2BFIkcxpDU9TrPJOygOJI%2Bz1JQki2rjDgA1MmBBCdiu9kqEzlNgKWwl2xmyAqocfk3Ywk8RvYiVcaYtPnEJHEoQuiyBofINyB%2BnF74PzTLRvYCrgeOqlTM6pWxsEiWyJPX%2B%2Fzm5g8pNjfjU1AOm0mM4lEEMg3kiLyL4EI4%2B7aA0kLQszeStqfQ6gf6MIczCuo3umV8DUn%2ByKgqvgoljiYPpjjwx2dFnPdv0F%2B%2FuTli76BxeFL3Sr%2F8A5tX%2F51p%2FPruaF3wyG2FcK%2FzmhcbGdo54TOMTBQEnQGcghiii%2Fgm13HfUWdchafTVyB%2BHyNylHGgqwh1pCl5ckaEC0K%2FNzBCG%2FB5z6BFjZzHTr8Nm%2BdqF4sp%2B7WU1TpLR0NvtNpU94fril1RRaboM28TkkEeFYhHhyMjuoHI2wI%2FySKmC41aXqsDvzek188Sa%2BLvOmhVJUBirxRFQ7jsC12BdCsSkzSPYkeilu6aOicRpu3zaq22uOJsZQsZMIDco5UGOqgByHAO1oI6QfFOMtooVHL35u6KTBgb8rDmo%2FJ%2FeMNHEqyVyKIc2vyhT%2Fx891dpxZEyeKcF%2FQXxmFSPG0%2Bovp2aeto50TndvLzCg7BQxpK5ToscD30w255US2d%2BTkYxhvmAQ4attnI5r%2BZTiYv0Tr2CtiZn3mkqCr2hMcWIMJkDUX8r4FFw4gULZCF5mIaKE%2FCjsFkhCZff93v07w1B2P2oWWhrJV2sYmJg&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20220614T211107Z&X-Amz-SignedHeaders=host&X-Amz-Expires=300&X-Amz-Credential=ASIAQ3PHCVTYYGJTZKMR%2F20220614%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Signature=a303cb3ca1c97e28c2e59000b2022e6846fb39df3c3ac815ae483ded7aa752e9&hash=03121177cc0b3925391ec76bccfda218737e736a72c6eb1d5ff3e1d9c24106dc&host=68042c943591013ac2b2430a89b270f6af2c76d8dfd086a07176afe7c76c2c61&pii=S1110016820303215&tid=spdf-0b21d045-9bc7-4816-bfd1-c0be0fd143cb&sid=39ec472a4164974ae43b8c906c6d5147cb45gxrqb&type=client&download=true&ua=4d57035655055955080350&rr=71b60e80fa4ab912

double computeOtsu(int *hist, int min, int max, int hauteur, int largeur)
{
    int i, j;
    double  moyen = 0.0, w0G, somme = 0.0, u0, var = 0.0, var1;
    double  varience, sq, difference;

    for (i = min; i <= max; i++)
    {
        //wt = wt + hist[i];
        moyen = moyen + i * hist[i];
        somme = somme + hist[i];
    }
    if (somme != 0.0)
    {
        w0G = somme / (hauteur * largeur); //calcu de la distribution de proba
        u0 = moyen / somme; //moyenne U1
        for (j = min; j <= max; j++)  //calcul de la varience 
        {
            difference = j - u0;
            sq = pow(difference, 2);
            var = var + (sq * hist[j]);
        }
        var1 = var / somme;
        varience = w0G * pow(var1, 2);
        return (varience);
    }
    else
        return (0.0);
}

int otsu(int hauteur, int largeur, Image img)
{

    float seuilT;
    double  var1 ,var_fg ,thes, temp ,varianceIntra[255], triIntra[255];
    int *hist = histo(img);

    int i, j, t ,seuil;
    // on appelle l'agorithme de otsu pour chaque seuil 
    for (t = 0; t < 254; t++)
    {
        var1 = computeOtsu(hist, 0, t, hauteur, largeur);
        var_fg = computeOtsu(hist, t + 1, 255, hauteur, largeur);
        varianceIntra[t] = var1 + var_fg;
        triIntra[t] = varianceIntra[t];
    }

    for (i = 1; i < 254; i++)
    {
        for (j = 1; j < 254 - i; j++)
        {

            if (varianceIntra[i] < varianceIntra[j])
            {
                temp = varianceIntra[i];
                varianceIntra[i] = varianceIntra[j];
                varianceIntra[j] = temp;
            }
        }
    }
    thes = varianceIntra[2];
    for (i = 1; i <= 255; i++)
    {
        if (triIntra[i] == thes)
            seuilT = i;
    }
    seuil = (int)seuilT;
    printf("le seuil min est %d" , seuil);
    return (seuil);
}

/*
void otsufINALE(Image img)
{
    int *hist = histo(img);
    int *Pi = calloc(255, sizeof(double)); //contient la distribution de proba de chaque niveau de gris
    double N = 0;
    double w0 = 0, w1 = 0, u0 = 0, u1 = 1, var1 = 0, var2 = 0, intra = 0; //N est le nombre totale de pixels
    double varianceIntra[255];
    int seuil = 0;
    double varmin;

    for (int T = 0; T < 255; T++)
    {

        for (int i = 0; i < 255; i++)
        {
            N += hist[i];
        }
        //calcul de la proba pour chaque niveau de gris
        for (int i = 0; i < 255; i++)
        {
            Pi[i] = (double)hist[i] / N;
        }

        //calcul des proba de chaque classe

        for (int i = 0; i < T; i++)
        {
            w0 += Pi[i];
        }
        for (int i = T; i < 255; i++)
        {
            w1 += Pi[i];
        }
        //calcul des moyennes de chaque classe
        for (int i = 0; i < T; i++)
        {
            u0 += i * Pi[i] / w0;
        }
        for (int i = T; i < 255; i++)
        {
            u1 += i * Pi[i] / w1;
        }
        // calcul des variances de chaque classse

        for (int i = 0; i < T; i++)
        {
            var1 += pow((i - u0), 2) * (Pi[i] / w0);
        }
        for (int i = T; i < 255; i++)
        {
            var2 += pow((i - u1), 2) ;
            printf("%f" , var2);
        }
        //calcul de la variance intraclasse
        varianceIntra[T] = w0 * var1 + w1 * var2;
        //printf("%f", w0 * var1 + w1 * var2);
    }
    varmin = varianceIntra[1];
    for (int i = 2; i < 255; i++)
    {
        if (varmin < varianceIntra[i])
        {
            seuil = i;
            varmin = varianceIntra[i];
            printf("var %d" ,i);
        }
    }
    //   free(v);
    printf("le seuil est ,%d", seuil);
    free(hist);
    free(Pi);
}
*/
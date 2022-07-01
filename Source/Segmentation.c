#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "../Header/Segmentation.h"
#include "../Header/Operations.h"

#include "../datastructure/header/LinkedList.h"
#include "../datastructure/header/structure.h"
#include "../datastructure/header/stack.h"


// Kmeans version optimale en espace memoire et temps de calcul
// K nombre de cluster
Image kmeansOptimale(Image m, int K)
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




//cette portion de code commenté permet de d  effectuer l'alo  comme A Automatique .ce qui
// est different dans le traitement des images
//permet de faire la distance entre le centroid et l'observation
/*
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
/
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
                pour mettre à jour le cluster , 
                premierement je calcule son nbre d'elements
                puisque ce sont les indices que je manipule , je crai une matrice qui contient la donnée
                relative à chaque cluster . A partir de cette matrice ,je mets à jour le cluster avec le calcul
                du centre de gravité. 
        

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
*/
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
    int seuil = otsu(img.largeur, img.hauteur, img);
    printf("\n\t La valeur optimale du seuil  est %d \n", seuil);
    Image m2 = binarisation(img, seuil);
    return m2;
}
//https://pdf.sciencedirectassets.com/270704/1-s2.0-S1110016820X00081/1-s2.0-S1110016820303215/main.pdf?X-Amz-Security-Token=IQoJb3JpZ2luX2VjEI3%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaCXVzLWVhc3QtMSJIMEYCIQC0BN7CijSJw7HsIGKvQupRQe7K0dwIzEbs7KFvg546GgIhALmQDgG352u7vEitZj5J9La%2FOfdsFDGBVNBhLB6%2B34%2BzKtsECJb%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEQBBoMMDU5MDAzNTQ2ODY1IgxBIMKIo8azOzPO2c0qrwTRlYcyAVEJIGqKcfOoapFXL7JYj7EfBiex3cvVnsB8BVnOXpXIeKvwpVeV4G5dxM66IoiHIWxm9oOrAoc%2BBD1VqFwS0r4gQo%2FgLYR7TeMxDMxNcpjXZE%2BfkheO5VsIL89ZOGHfKYuj0hNYCIbyNkuFIq7PXspNyukE74XKuY%2FBXQCx%2FMyzS3brgOSgm9AZKBNAEbQBWGcgZxawfDsrrLNJbZLUauqN9OdHGIt8HJNZ077R3Ii8Kp85I86%2BFIkcxpDU9TrPJOygOJI%2Bz1JQki2rjDgA1MmBBCdiu9kqEzlNgKWwl2xmyAqocfk3Ywk8RvYiVcaYtPnEJHEoQuiyBofINyB%2BnF74PzTLRvYCrgeOqlTM6pWxsEiWyJPX%2B%2Fzm5g8pNjfjU1AOm0mM4lEEMg3kiLyL4EI4%2B7aA0kLQszeStqfQ6gf6MIczCuo3umV8DUn%2ByKgqvgoljiYPpjjwx2dFnPdv0F%2B%2FuTli76BxeFL3Sr%2F8A5tX%2F51p%2FPruaF3wyG2FcK%2FzmhcbGdo54TOMTBQEnQGcghiii%2Fgm13HfUWdchafTVyB%2BHyNylHGgqwh1pCl5ckaEC0K%2FNzBCG%2FB5z6BFjZzHTr8Nm%2BdqF4sp%2B7WU1TpLR0NvtNpU94fril1RRaboM28TkkEeFYhHhyMjuoHI2wI%2FySKmC41aXqsDvzek188Sa%2BLvOmhVJUBirxRFQ7jsC12BdCsSkzSPYkeilu6aOicRpu3zaq22uOJsZQsZMIDco5UGOqgByHAO1oI6QfFOMtooVHL35u6KTBgb8rDmo%2FJ%2FeMNHEqyVyKIc2vyhT%2Fx891dpxZEyeKcF%2FQXxmFSPG0%2Bovp2aeto50TndvLzCg7BQxpK5ToscD30w255US2d%2BTkYxhvmAQ4attnI5r%2BZTiYv0Tr2CtiZn3mkqCr2hMcWIMJkDUX8r4FFw4gULZCF5mIaKE%2FCjsFkhCZff93v07w1B2P2oWWhrJV2sYmJg&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20220614T211107Z&X-Amz-SignedHeaders=host&X-Amz-Expires=300&X-Amz-Credential=ASIAQ3PHCVTYYGJTZKMR%2F20220614%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Signature=a303cb3ca1c97e28c2e59000b2022e6846fb39df3c3ac815ae483ded7aa752e9&hash=03121177cc0b3925391ec76bccfda218737e736a72c6eb1d5ff3e1d9c24106dc&host=68042c943591013ac2b2430a89b270f6af2c76d8dfd086a07176afe7c76c2c61&pii=S1110016820303215&tid=spdf-0b21d045-9bc7-4816-bfd1-c0be0fd143cb&sid=39ec472a4164974ae43b8c906c6d5147cb45gxrqb&type=client&download=true&ua=4d57035655055955080350&rr=71b60e80fa4ab912

double computeOtsu(int *hist, int min, int max, int hauteur, int largeur)
{
    int i, j;
    double moyen = 0.0, w0G, somme = 0.0, u0, var = 0.0, var1;
    double varience, sq, difference;

    for (i = min; i <= max; i++)
    {
        //wt = wt + hist[i];
        moyen = moyen + i * hist[i];
        somme = somme + hist[i];
    }
    if (somme != 0.0)
    {
        w0G = somme / (hauteur * largeur); //calcu de la distribution de proba
        u0 = moyen / somme;                //moyenne U1
        for (j = min; j <= max; j++)       //calcul de la varience
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
    double var1, var_fg, thes, temp, varianceIntra[255], triIntra[255];
    int *hist = histo(img);

    int i, j, t, seuil;
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
    printf("le seuil min est %d", seuil);
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

int** copy_matrix(int** mat , int largeur , int hauteur){
    int** m = generate_matrice(largeur, hauteur);
    for (int i = 0; i < largeur; i++)
    {
        for (int j = 0; j < hauteur; j++)
        {
            m[i][j]= mat[i][j];
        }
        
    }
    return m;
}

double moyenne(int* hist , int debut , int fin){
   double m= 0;
   for (int i = debut; i < fin; i++)
   {
       m += hist[i] ;
   }
   return m/(debut-fin);
}

void seuillage_automatique(Image m){

    
}


Image croissance_des_regions(Image image, int nombre_de_germe, int seuil)
{
    typedef struct Point Point;
    List* germ_tab = calloc(nombre_de_germe , sizeof(List));

    int i = 0 , j = 0 , x , y;
    for (i = 0; i < nombre_de_germe; i++)
    {//printf("entrerr");
        x = rand() % image.largeur;
        y = rand() % image.hauteur;
      //  printf("x %d , y %d , couleur %d \n", x, y ,image.M[x][y] );
        Point *p = new_Point(x , y , image.M[x][y]);
        List germ = dispersion_des_germes(p , image , seuil);
        germ_tab[i] = germ;
        printf("taille du germe %d %d\n" ,i, germ->length);
    }
    
    Image result ;
    result.M =  generate_matrice(image.largeur , image.hauteur);
    for (i = 0; i < nombre_de_germe; i++)
    {
        List germ = germ_tab[i];
        for (j = 0; j < germ->length; j++)
        {
            Point *p = get_element_list(germ, j);
            result.M[p->x][p->y] = p->color;
         //   printf("coleur %d , M %d\n" ,p->color , M_R[p->x][p->y]  );
        }
    }
    result.MAX_PIXEL_VALUE = 255;
    strcpy(result.name , "P2");
    strcpy(result.description , "# croissance des regions");
    result.hauteur = image.hauteur;
    result.largeur = image.largeur;

    for (i = 0; i < nombre_de_germe; i++)
    {
        List germ = germ_tab[i];
        for (j = 0; j < germ->length ; j++)
        {
            Point *p = get_element_list(germ , j);
            free(p);
        }
        free_list(germ);
    }
    
    free(germ_tab);
    return result;
}

List bon_voisin(Image image, struct Point *point, int seuil){
    typedef struct Point Point;
    int i = 0 , j;
    int **M = image.M ;
    List result = new_list();
    for (i = point->x - 1 ; i <= point->x + 1; i++)
    {
        for (j = point->y - 1; j <= point->y + 1; j++)
        {
            if(i < image.largeur && i > 0 && j < image.hauteur && j > 0 && i != point->x && j != point->y){
                if (abs(point->color - M[i][j]) <= seuil)
                {
                    Point *temp_p = new_Point(i , j , M[i][j]);
                    queue_insertion(result , temp_p);
                }
            }
        }
    }

    return result;
}

List dispersion_des_germes(struct Point *point, Image image, int seuil)
{
    int i = 0;
    typedef struct Point Point;
    Stack stack = new_stack();
    List germs = new_list();

    push(stack , point);
    while (is_empty_stack(stack) == False)
    {
        Point *temp_p = pop(stack);
        queue_insertion(germs , temp_p);
        List temp_list = bon_voisin(image , temp_p , seuil);
        for (i = 0; i < temp_list->length; i++)
        {
            Point *temp_p1 = get_element_list(temp_list, i);
            if(search_value_in_list(germs , temp_p1, equal_point) == False){
                push(stack , temp_p1);
            }
        }
        free_list(temp_list);
    }

    free_stack(stack);
    return germs;
}


// cette version est sous optimale car utilisation d'une liste chainee pour stocker les 
// centres . ce qui occupe de la mémoire et augmente le temps de calcul
Image kmeans_f_niveau_de_gris(Image image, int nbr_cluster)
{
    typedef struct Point Point;
    int i = 0, x = 0, y = 0, color , j = 0;
    List gabageCollector = new_list();  //permet de rammasser les elements non utilisés
    int compteur =0;
    // initialisation de la liste des cluster
    
    Point **center_tab = calloc(nbr_cluster , sizeof(Point*));
    for (i = 0; i < nbr_cluster; i++)
    {
        // initialisation des centres des nbr_cluster
        x = rand() % image.largeur;
        y = rand() % image.hauteur;
        color = image.M[i][j];
        printf("x %d , y %d\n" , x , y);
        Point *point = new_Point(x, y, color);
        queue_insertion(gabageCollector, point);
        center_tab[i] = point;
    }

    //initialisation des cluster
    List *clusters_tab = initialiseCluster(image.M , image.largeur , image.hauteur , center_tab , nbr_cluster , gabageCollector);
    boolean stable = True;
    do
    {
        center_tab = calloc(nbr_cluster, sizeof(Point *));
        for (i = 0; i < nbr_cluster; i++)
        {
            center_tab[i] = calcul_centre(clusters_tab[i]);
        }


        List *new_cluster_tab = reassignment(clusters_tab , (const struct Point**)center_tab, nbr_cluster);
        
        for (i = 0; i < nbr_cluster; i++)
        {
            int r1 = rand() % clusters_tab[i]->length;
            int r2 = rand() % clusters_tab[i]->length;

            Point *p1 = get_element_list(clusters_tab[i], r1);
            Point *p2 = get_element_list(clusters_tab[i], r2);
            printf("length :%d color1 : %d color2 : %d\n", clusters_tab[i]->length, p1->color, p2->color);
        }

        for (i = 0; i < nbr_cluster; i++)

        {
            int r1 = rand() % new_cluster_tab[i]->length;
            int r2 = rand() % new_cluster_tab[i]->length;

            Point *p1 = get_element_list(new_cluster_tab[i], r1);
            Point *p2 = get_element_list(new_cluster_tab[i], r2);
            printf("length :%d color1 : %d color2 : %d\n", new_cluster_tab[i]->length, p1->color, p2->color);
        }
        
        stable = is_stable(new_cluster_tab, clusters_tab, nbr_cluster);

        free_set_of_cluster(clusters_tab, nbr_cluster);
        clusters_tab = new_cluster_tab;

        for (i = 0; i < nbr_cluster; i++)
        {
            free(center_tab[i]);
        }
        free(center_tab);
        compteur++ ;
    } while (stable == False || compteur != 1000);
Image result = create_image(image);
    for (i = 0; i < nbr_cluster; i++)
    {
        List cluster = clusters_tab[i];
        for (j = 0; j < cluster->length; j++)
        {
            Point *p = get_element_list(cluster , j);
            result.M[p->x][p->y] = p->color;
        }
        
    }

    for (i = 0; i < gabageCollector->length; i++)
    {
        free(get_element_list(gabageCollector, i));
    }
    free_list(gabageCollector);
    free_set_of_cluster(clusters_tab , nbr_cluster);
    return result;
}

void free_set_of_cluster(List *tab, int nbr_cluster)
{
    int i = 0;
    for (i = 0; i < nbr_cluster; i++)
    {
        free_cluster(tab[i]);
    }
    free(tab);
}

void free_cluster(List cluster)
{
    free_list(cluster);
}

struct Point *copy_point(const struct Point *point)
{
    return new_Point(point->x, point->y, point->color);
}

List copy_cluster(const List cluster)
{
    List cluster_copy = new_list();
    int i = 0;
    for (i = 0; i < cluster->length; i++)
    {
        queue_insertion(cluster_copy, get_element_list(cluster, i));
    }
    return cluster_copy;
}

List *copie_ensemble_cluster(const List *cluster_tab, int nbr_cluster)
{
    int i = 0;
    List *cluster_tab_copy = calloc(nbr_cluster, sizeof(List));
    for (i = 0; i < nbr_cluster; i++)
    {
        cluster_tab_copy[i] = copy_cluster(cluster_tab[i]);
    }

    return cluster_tab_copy;
}

struct Point *calcul_centre(const List cluster)
{
    typedef struct Point Point;
    int i = 0, x = 0, y = 0, color;
    Point *p;
    if(is_empty_list(cluster) == True)
        return NULL;
    
    for (i = 0; i < cluster->length; i++)
    {
        p = get_element_list(cluster, i);
        x += p->x;
        y += p->y;
    }
    x /= cluster->length;
    y /= cluster->length;
    color = p->color;
    return new_Point(x, y, color);
}

float calculate_distance(const struct Point *point1, const struct Point *point2)
{
    return sqrt(pow(point2->y - point1->y, 2) + pow(point2->x - point1->x, 2));
}

int* point_proche_centre(const struct Point *point, const struct Point **center_tab, int nbr_cluster)
{
    int *tuple = calloc(2 ,sizeof(int));
    int i = 0, index = 0 ;
    float d, min = 0.0;
    min = calculate_distance(point, center_tab[0]);
    for (i = 1; i < nbr_cluster; i++)
    {
        if(center_tab[i] != NULL){
            d = calculate_distance(point, center_tab[i]);
            if (d < min)
            {
                min = d;
                index = i;
            }
        }
    }
    tuple[0] = index;
    tuple[1] = center_tab[index]->color;
    return tuple;
}

List *reassignment(const List *cluster_tab, const struct Point **center_tab, int nbr_cluster)
{
    typedef struct Point Point;
    int i = 0, j = 0, index = 0;
    List *new_cluster_tab = calloc(nbr_cluster, sizeof(List));
    for (i = 0; i < nbr_cluster; i++)
    {
        new_cluster_tab[i] = new_list();
    }

    for (i = 0; i < nbr_cluster; i++)
    {
        List cluster = cluster_tab[i];
        if(cluster != NULL){
            for (j = 0; j < cluster->length; j++)
            {
                Point *point = get_element_list(cluster, j);
                int *tuple = point_proche_centre(point, center_tab, nbr_cluster);
                if (tuple[0] != i)
                {
                    delete_element_list(cluster, j);
                    j--;
                    point->color = tuple[1];
                    queue_insertion(new_cluster_tab[tuple[0]], point);
                }else{
                    point->color = center_tab[i]->color;
                    queue_insertion(new_cluster_tab[i], point);
                }
                free(tuple);
            }
        }
    }

    return new_cluster_tab;
}



boolean is_stable(const List *new_cluster_tab, const List *old_cluster_tab, int nbr_cluster)
{
    boolean stable = True;
    int i = 0, j = 0;
    do
    {
        if (new_cluster_tab[i]->length != old_cluster_tab[i]->length){
            stable = False;
        }else{
            if (include_value_list(new_cluster_tab[i], old_cluster_tab[i], equal_point) == False)
            {
                stable = False;
            }
        }
        i++;
    } while (stable == True && i < nbr_cluster);
    return stable;
}

List *initialiseCluster(int **M , int nbr_line , int nbr_col , struct Point **center_tab , int nbr_cluster , List gabageCollector){
    typedef struct Point Point;
    int i = 0 , j = 0;
    List *clusters_tab = calloc(nbr_cluster, sizeof(List));
    List cluster = new_list();
    for (i = 0; i < nbr_line; i++)
    {
        for (j = 0; j < nbr_col; j++)
        {

            Point *point = new_Point(i , j, M[i][j]);
            queue_insertion(gabageCollector, point);
            queue_insertion(cluster , point);
        }
    }

    clusters_tab[0] = cluster; 
    List *result = reassignment(clusters_tab, (const struct Point**)center_tab, nbr_cluster);
    free_set_of_cluster(clusters_tab , nbr_cluster);
    return result;    
}

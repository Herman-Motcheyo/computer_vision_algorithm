#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Util.h"
#include <time.h>
#include <string.h>

void afficher(bit *clusters, short a, int b)
{
  for (int i = 0; i < a; i++)
  {
    for (int j = 0; j < b; j++)
    {
      printf("%d, ", clusters[i * b + j]);
    }
    printf("\n");
  }
  printf("\n");
}

int comprare_cluster(bit *prevCluster, bit *currCuster, short a, int b)
{
  for (int i = 0; i < a; i++)
  {
    for (int j = 0; j < b; j++)
    {
      if (prevCluster[i * b + j] != currCuster[i * b + j])
      {
        return 0;
      }
    }
  }
  return 1;
}

void initialize_cluster(bit *clusters, short clustercount)
{
  printf("Centre initiaux: \n\n");
  // Initializing clusters
  srand(time(NULL));
  for (int i = 0; i < clustercount; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      clusters[i * 3 + j] = rand() % 256;
      printf("%d, ", clusters[i * 3 + j]);
    }
    printf("\n");
  }
}

void recalcul_cluster(bit *bitmap, bit *clusters, short clustercount, bit *labels, int largeur, int hauteur)
{
  for (int i = 0; i < clustercount; i++)
  {
    int count = 0;
    float pixelsum[3];
    for (int j = 0; j < 3; j++)
    {
      pixelsum[j] = 0;
    }
    for (int j = 0; j < largeur; j++)
    {
      for (int k = 0; k < hauteur; k++)
      {
        if (labels[j * hauteur + k] == i)
        {
          for (int l = 0; l < 3; l++)
          {
            pixelsum[l] += bitmap[(j * hauteur + k) * 3 + l];
          }
          count++;
        }
      }
    }
    for (int l = 0; l < 3; l++)
    {
      clusters[i * 3 + l] = pixelsum[l] / count;
    }
  }
}

int GetClusterPixelIndex(bit *pixel, bit *clusters, short clustercount)
{
  // Assign pixel to cluster
  int min_dist = -1, dist, clusterIndex;
  for (int i = 0; i < clustercount; i++)
  {
    dist = 0;
    for (int j = 0; j < 3; j++)
    {
      dist = dist + pow(pixel[j] - clusters[(i * 3 + j)], 2);
    }
    dist = sqrt(dist);
    if (dist < min_dist || min_dist == -1)
    {
      min_dist = dist;
      clusterIndex = i;
    }
  }

  return clusterIndex;
}

void GetClusteredImage(bit *bitmap, bit *clustermap, bit *clusters, bit *labels, short clustercount, int largeur, int hauteur)
{
  bit pixel[3];
  int clusterIndex;
  for (int i = 0; i < largeur; i++)
  {
    for (int j = 0; j < hauteur; j++)
    {
      for (int k = 0; k < 3; k++)
      {
        pixel[k] = bitmap[(i * hauteur + j) * 3 + k];
      }
      clusterIndex = GetClusterPixelIndex(pixel, clusters, clustercount);
      for (int k = 0; k < 3; k++)
      {
        pixel[k] = clusters[clusterIndex * 3 + k];
      }
      for (int l = 0; l < 3; l++)
      {
        clustermap[(i * hauteur + j) * 3 + l] = pixel[l];
      }
      // Assign Label
      labels[i * hauteur + j] = clusterIndex;
    }
  }
}

void mise_a_jour_cluster(bit *prevCluster, bit *currCuster, short a, int b)
{
  for (int i = 0; i < a; i++)
  {
    for (int j = 0; j < b; j++)
    {
      prevCluster[i * b + j] = currCuster[i * b + j];
    }
  }
}

void Kmeans(bit *bitmap, bit *clustermap, bit *clusters, bit *labels, short clustercount, int largeur, int hauteur, int iterations)
{
  bit *prevClusters = (bit *)malloc(clustercount * 3 * sizeof(bit));

  initialize_cluster(clusters, clustercount);

  for (int i = 0; i < iterations; i++)
  {
    //afficher(clusters, clustercount, 3);

    if (comprare_cluster(prevClusters, clusters, clustercount, 3) && i != 0)
    {
      printf("No. of iterations: %d\n\n", i + 1);
      break;
    }

    mise_a_jour_cluster(prevClusters, clusters, clustercount, 3);

    GetClusteredImage(bitmap, clustermap, clusters, labels, clustercount, largeur, hauteur);

    recalcul_cluster(bitmap, clusters, clustercount, labels, largeur, hauteur);
  }
}

int main(int argc, char *argv[])
{
  FILE *ifp;
  bit *bitmap, *clustermap, *clusters, *labels;
  int ich1, ich2, largeur, hauteur, maxval = 255, ppmraw;
  int i, j, k;
  short cluster_count;

  /* Arguments */
  if (argc !=3 )
  {
    printf("\nUsage: %s Vous devez avoir 3 args: ./kmeans Fichier nbcluster \n\n", argv[0]);
  }

  /* Opening */
  ifp = fopen(argv[1], "r");
  if (ifp == NULL)
  {
    printf("Impossible d'ouvrir le fichier %s\n", argv[1]);
    exit(1);
  }

  cluster_count = atoi(argv[2]);

  ich1 = getc(ifp);
  if (ich1 == EOF)
    pm_erreur("EOF / erreur de lecture / magic number");
  ich2 = getc(ifp);
  if (ich2 == EOF)
    pm_erreur("EOF /erreur de lecture / magic number");
  if (ich2 != '3' && ich2 != '6')
    pm_erreur(" mauvais fichier ");
  else if (ich2 == '3')
    ppmraw = 0;
  else
    ppmraw = 1;

  hauteur = pm_getint(ifp);
  largeur = pm_getint(ifp);
  maxval = pm_getint(ifp);
 char logiciel[10] = "eog";
  bitmap = (bit *)malloc(hauteur * largeur * 3 * sizeof(bit));
  clustermap = (bit *)malloc(hauteur * largeur * 3 * sizeof(bit));

  clusters = (bit *)malloc(cluster_count * 3 * sizeof(bit));

  // Label Matrix
  labels = (bit *)malloc(hauteur * largeur * sizeof(bit));

  /* Reading */
  for (i = 0; i < largeur; i++)
    for (j = 0; j < hauteur; j++)
      for (k = 0; k < 3; k++)
        if (ppmraw)
          bitmap[(i * hauteur + j) * 3 + k] = pm_getrawbyte(ifp);
        else
          bitmap[(i * hauteur + j) * 3 + k] = pm_getint(ifp);

  Kmeans(bitmap, clustermap, clusters, labels, cluster_count, largeur, hauteur, 1000);

  FILE *ifpWrite = fopen("image/kmeansCouleur.ppm", "w");

  if (ppmraw)
    fprintf(ifpWrite, "P3\n");
  else
    printf("P6\n");

  fprintf(ifpWrite, "%d %d \n", hauteur, largeur);
  fprintf(ifpWrite, "%d\n", maxval);

  for (i = 0; i < largeur; i++)
    for (j = 0; j < hauteur; j++)
      for (k = 0; k < 3; k++)
        if (ppmraw)
          fprintf(ifpWrite, "%d ", clustermap[(i * hauteur + j) * 3 + k]);
        else
          fprintf(ifpWrite, "%c", clustermap[(i * hauteur + j) * 3 + k]);
  free(bitmap);
  free(clustermap);
  free(clusters);
  free(labels);
     strcat(logiciel, "  image/kmeansCouleur.ppm");
      system(logiciel);
  /* Closing */
  fclose(ifp);
  fclose(ifpWrite);
  exit(0);
}

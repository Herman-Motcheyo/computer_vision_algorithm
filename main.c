#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "./Header/Contour.h"
#include "./Header/Segmentation.h"

int main(int argc, char *argv[])
{
  FILE *file = NULL;
  printf("\nfichier 1 , %s\n", argv[2]);
 // printf("\nfichier 1 , %s\n", argv[3]);
  char logiciel[10] = "eog";
  if (argc == 2)
  {
      printf("Impossible d'executer une action aucun parametre de correspond à %s" , argv[1]);
      exit(1);
  }
  
  if (argc == 3)
  {
    if (strcmp("histogramme", argv[1]) == 0)
    {
      file = fopen(argv[2], "r");
      if (file == NULL)
      {
        printf("chemin du fichier  incorrect");
        exit(1);
      }

      Image m = read_Image_file(argv[2]);
      histogramme(m);
      Image m2 = egalisation_histogramme(m);

      strcat(logiciel, "  image/histo/histogramme.pgm");
      system(logiciel);
      histogramme(m2);

      strcat(logiciel, "  image/histo/histogramme.pgm");
      system(logiciel);
      freeMatrice(m2.M, m2.largeur);
      freeMatrice(m.M, m.largeur);
      fclose(file);
      exit(0);
    }
    else if (strcmp("egalisation", argv[1]) == 0)
    {

      file = fopen(argv[2], "r");
      if (file == NULL)
      {
        printf("chemin du fichier  incorrect");
        exit(1);
      }
      Image eg = read_Image_file(argv[2]);
      Image ega = egalisation_histogramme(eg);
      write_Image_to_file(ega, "image/Image_egalise.pgm");

      strcat(logiciel, "  image/Image_egalise.pgm");
      system(logiciel);
      freeMatrice(ega.M, ega.largeur);
      freeMatrice(eg.M, eg.largeur);
      fclose(file);
      exit(0);
    }else if (strcmp("ho", argv[1]) == 0)
    {

      file = fopen(argv[2], "r");
      if (file == NULL)
      {
        printf("chemin du fichier  incorrect");
        exit(1);
      }
      Image eg = read_Image_file(argv[2]);
      houghv2( eg);
      strcat(logiciel, "  ./image/hougth.pgm");
      system(logiciel);
      freeMatrice(eg.M, eg.largeur);
      fclose(file);
      exit(0);
    }
    else if (strcmp("not", argv[1]) == 0)
    {

      file = fopen(argv[2], "r");
      if (file == NULL)
      {
        printf("chemin du fichier  incorrect");
        exit(1);
      }
      Image eg = read_Image_file(argv[2]);
      Image ega = not(eg);
      write_Image_to_file_Pbm(ega, "image/not_image.pgm");

      strcat(logiciel, "  image/not_image.pgm");
      system(logiciel);
      freeMatrice(ega.M, ega.largeur);
      freeMatrice(eg.M, eg.largeur);
      fclose(file);
      exit(0);
    }
    else if (strcmp("transpose", argv[1]) == 0)
    {
      file = fopen(argv[2], "r");
      if (file == NULL)
      {
        printf("chemin du fichier %s incorrect ", argv[2]);
        exit(1);
      }
      Image t = read_Image_file(argv[2]);
      Image tr = transpose_Image(t);
      write_Image_to_file(tr, "image/Image_transpose.pgm");

      strcat(logiciel, "  image/Image_transpose.pgm");
      system(logiciel);
      freeMatrice(t.M, t.largeur);
      freeMatrice(tr.M, tr.largeur);
      fclose(file);
      exit(0);
    }
    else if (strcmp("trans_lineaire", argv[1]) == 0)
    {
      file = fopen(argv[2], "r");
      if (file == NULL)
      {
        printf("chemin du fichier %s incorrect ", argv[2]);
        exit(1);
      }
      Image trans = read_Image_file(argv[2]);
      Image transf = transpose_Image(trans);
      write_Image_to_file(transf, "image/transformation_lineaire_image.pgm");

      strcat(logiciel, "  image/transformation_lineaire_image.pgm");
      system(logiciel);
      freeMatrice(trans.M, trans.largeur);
      freeMatrice(transf.M, transf.largeur);
      fclose(file);
      exit(0);
    }
    else if (strcmp("inverse", argv[1]) == 0)
    {

      file = fopen(argv[2], "r");
      if (file == NULL)
      {
        printf("chemin du fichier %s incorrect ", argv[2]);
        exit(1);
      }
      Image n = read_Image_file(argv[2]);
      Image ni = negatif_image(n);
      write_Image_to_file(ni, "image/inverse_image.pgm");

      strcat(logiciel, "  image/inverse_image.pgm");
      system(logiciel);
      freeMatrice(n.M, n.largeur);
      freeMatrice(ni.M, ni.largeur);
      fclose(file);
      exit(0);
    }
    else if (strcmp("luminance", argv[1]) == 0)
    {

      file = fopen(argv[2], "r");
      if (file == NULL)
      {
        printf("chemin du fichier %s incorrect ", argv[2]);
        exit(1);
      }
      Image lu = read_Image_file(argv[2]);
      Image lui = luminanceImage(lu);
      write_Image_to_file(lui, "image/luminance_image.pgm");

      strcat(logiciel, "  image/luminance_image.pgm");
      system(logiciel);
      freeMatrice(lui.M, lui.largeur);
      freeMatrice(lu.M, lu.largeur);
      fclose(file);
      exit(0);
    }


    else if (strcmp("c-lap", argv[1]) == 0)
    {

      file = fopen(argv[2], "r");
      if (file == NULL)
      {
        printf("chemin du fichier %s incorrect ", argv[2]);
        exit(1);
      }
      Image cpla = read_Image_file(argv[2]);
      contour(cpla ,  "laplacien" ,0);
      strcat(logiciel, "  image/laplacien_contour.pgm");
      system(logiciel);
      fclose(file);
      exit(0);
    }
    else if (strcmp("contraste", argv[1]) == 0)
    {

      file = fopen(argv[2], "r");
      if (file == NULL)
      {
        printf("chemin du fichier %s incorrect ", argv[2]);
        exit(1);
      }
      Image lu = read_Image_file(argv[2]);
      Image lui = contrasteImage(lu);
      write_Image_to_file(lui, "image/constraste_image.pgm");

      strcat(logiciel, "  image/constraste_image.pgm");
      system(logiciel);
      freeMatrice(lui.M, lui.largeur);
      freeMatrice(lu.M, lu.largeur);
      fclose(file);
      exit(0);
    }
    else if (strcmp("otsu", argv[1]) == 0)
    {

      file = fopen(argv[2], "r");
      if (file == NULL)
      {
        printf("chemin du fichier %s incorrect ", argv[2]);
        exit(1);
      }
      Image lu = read_Image_file(argv[2]);
      Image lui = seuillageAutomatique(lu);
      write_Image_to_file(lui, "image/otsu_image.pbm");

      strcat(logiciel, "  image/otsu_image.pbm");
      system(logiciel);
      freeMatrice(lui.M, lui.largeur);
      freeMatrice(lu.M, lu.largeur);
      fclose(file);
      exit(0);
    }
    else
    {
      printf("Impossible d'executer une action aucun parametre de correspond à %s" , argv[1]);
      exit(1);
    }
  }
  else if (argc == 4)
  {
    char logiciel[10] = "eog";
    FILE *file2 = NULL;

    if (strcmp("addition", argv[1]) == 0)
    {
      file = fopen(argv[2], "r");
      file2 = fopen(argv[3], "r");
      if (file == NULL && file2 == NULL)
      {
        printf("le chemin specifier pour fichier %s ou pour fichier %s est invalide", argv[2], argv[3]);
        exit(1);
      }
      Image img1 = read_Image_file(argv[2]);
      Image img2 = read_Image_file(argv[3]);
      Image add = addition(img1, img2);
      write_Image_to_file(add, "image/addition_image.pgm");

      strcat(logiciel, "  image/addition_image.pgm");
      system(logiciel);
      freeMatrice(img1.M, img1.largeur);
      freeMatrice(img2.M, img2.largeur);
      freeMatrice(add.M, add.largeur);
      fclose(file);
      exit(0);
    }
    else if (strcmp("soustraction", argv[1]) == 0)
    {
      file = fopen(argv[2], "r");
      file2 = fopen(argv[3], "r");
      if (file == NULL && file2 == NULL)
      {
        printf("le chemin specifier pour fichier %s ou pour fichier %s est invalide", argv[2], argv[3]);
        exit(1);
      }
      Image img1 = read_Image_file(argv[2]);
      Image img2 = read_Image_file(argv[3]);
      Image sou = soustration(img1, img2);
      write_Image_to_file(sou, "image/soustraction_image.pgm");

      strcat(logiciel, "  image/soustraction_image.pgm");
      system(logiciel);
      freeMatrice(img1.M, img1.largeur);
      freeMatrice(img2.M, img2.largeur);
      freeMatrice(sou.M, sou.largeur);
      fclose(file);
      fclose(file2);
      exit(0);
    }
    else if (strcmp("multiplication", argv[1]) == 0)
    {
      file = fopen(argv[2], "r");
      if (file == NULL && file2 == NULL)
      {
        printf("le chemin specifier pour fichier %s est invalide", argv[2]);
        exit(1);
      }
      float ratio = atoi(argv[3]);
      Image img1 = read_Image_file(argv[2]);
      Image sou = multiplication(img1, ratio);
      write_Image_to_file(sou, "image/multiplication_image_ratio.pgm");

      strcat(logiciel, "  image/multiplication_image_ratio.pgm");
      system(logiciel);
      freeMatrice(img1.M, img1.largeur);
      freeMatrice(sou.M, sou.largeur);
      fclose(file);
      exit(0);
    }
    else if (strcmp("binarisation", argv[1]) == 0)
    {

      file = fopen(argv[2], "r");
      if (file == NULL)
      {
        printf("le chemin specifier pour fichier %s est invalide", argv[2]);
        exit(1);
      }
      Image img1 = read_Image_file(argv[2]);
      int seuil = atoi(argv[3]);
      Image add = binarisation(img1, seuil);
      write_Image_to_file_Pbm(add, "image/binarisation_image.pbm");

      strcat(logiciel, "  image/binarisation_image.pbm");
      system(logiciel);
      freeMatrice(img1.M, img1.largeur);
      freeMatrice(add.M, add.largeur);
      fclose(file);
      exit(0);
    }
    else if (strcmp("and", argv[1]) == 0)
    {
      file = fopen(argv[2], "r");
      file2 = fopen(argv[3], "r");
      if (file == NULL && file2 == NULL)
      {
        printf("le chemin specifier pour fichier %s ou pour fichier %s est invalide", argv[2], argv[3]);
        exit(1);
      }
      Image img1 = read_Image_file(argv[2]);
      Image img2 = read_Image_file(argv[3]);
      Image sou = and(img1, img2);
      write_Image_to_file_Pbm(sou, "image/and_image.pbm");

      strcat(logiciel, "  image/and_image.pbm");
      system(logiciel);
      freeMatrice(img1.M, img1.largeur);
      freeMatrice(img2.M, img2.largeur);
      freeMatrice(sou.M, sou.largeur);
      fclose(file);
      fclose(file2);
      exit(0);
    }
    else if (strcmp("or", argv[1]) == 0)
    {
      file = fopen(argv[2], "r");
      file2 = fopen(argv[3], "r");
      if (file == NULL && file2 == NULL)
      {
        printf("le chemin specifier pour fichier %s ou pour fichier %s est invalide", argv[2], argv[3]);
        exit(1);
      }
      Image img1 = read_Image_file(argv[2]);
      Image img2 = read_Image_file(argv[3]);
      Image sou = or (img1, img2);
      write_Image_to_file_Pbm(sou, "image/or_image.pbm");

      strcat(logiciel, "  image/or_image.pbm");
      system(logiciel);
      freeMatrice(img1.M, img1.largeur);
      freeMatrice(img2.M, img2.largeur);
      freeMatrice(sou.M, sou.largeur);
      fclose(file);
      fclose(file2);
      exit(0);
    }
    else if (strcmp("xor", argv[1]) == 0)
    {
      file = fopen(argv[2], "r");
      file2 = fopen(argv[3], "r");
      if (file == NULL && file2 == NULL)
      {
        printf("le chemin specifier pour fichier %s ou pour fichier %s est invalide", argv[2], argv[3]);
        exit(1);
      }
      Image img1 = read_Image_file(argv[2]);
      Image img2 = read_Image_file(argv[3]);
      Image sou = xor(img1, img2);
      write_Image_to_file_Pbm(sou, "image/xor_image.pbm");

      strcat(logiciel, "  image/xor_image.pbm");
      system(logiciel);
      freeMatrice(img1.M, img1.largeur);
      freeMatrice(img2.M, img2.largeur);
      freeMatrice(sou.M, sou.largeur);
      fclose(file);
      fclose(file2);
      exit(0);
    }
    else if (strcmp(argv[1], "-c") == 0)
    {

      file = fopen(argv[2], "r");
      file2 = fopen(argv[3], "r");
      if (file == NULL || file2 == NULL)
      {
        printf("le chemin specifier pour fichier %s ou pour fichier %s est invalide", argv[2], argv[3]);
        exit(1);
      }
      Image img1 = read_Image_file(argv[2]);
      Image sou = convolution_filter_path(img1, argv[3]);
      write_Image_to_file(sou, "image/convolution_filter.pgm");
      printf("le fichier à ete generé dans image/convolution_filter.pgm ");

      strcat(logiciel, "  image/convolution_filter.pgm");
      system(logiciel);
      freeMatrice(img1.M, img1.largeur);
      freeMatrice(sou.M, sou.largeur);
      fclose(file);
      fclose(file2);
      exit(0);
    }else if (strcmp("c-d" , argv[1])==0 )
    {
      
      file = fopen(argv[2], "r");
      int seuil = atoi(argv[3]);
      if (file == NULL)
      {
        printf("le chemin specifier pour fichier %s ou pour fichier %s est invalide", argv[2], argv[3]);
        exit(1);
      }
      Image img1 = read_Image_file(argv[2]);
      Image sou = derive(img1, seuil);
      write_Image_to_file(sou, "image/derive_contour.pgm");
      printf("le fichier à ete generé dans image/derive_contour.pgm ");

      strcat(logiciel, "  image/derive_contour.pgm");
      system(logiciel);
      freeMatrice(img1.M, img1.largeur);
      freeMatrice(sou.M, sou.largeur);
      fclose(file);
      exit(0);
    }
    else if (strcmp(argv[1], "c-sp") == 0)
    {

      file = fopen(argv[2], "r");
      file2 = fopen(argv[3], "r");
      if (file == NULL || file2 == NULL)
      {
        printf("le chemin specifier pour fichier %s ou pour fichier %s est invalide", argv[2], argv[3]);
        exit(1);
      }
      Image img1 = read_Image_file(argv[2]);
      Image sou = contour_filtersansSeuil(argv[3], img1);
      write_Image_to_file(sou, "image/contour_S_P_SansSeuil.pgm");
      printf("le fichier à ete generé dans image/contour_S_P_SansSeuil.pgm ");

      strcat(logiciel, "  image/contour_S_P_SansSeuil.pgm");
      system(logiciel);
      freeMatrice(img1.M, img1.largeur);
      freeMatrice(sou.M, sou.largeur);
      fclose(file);
      fclose(file2);
      exit(0);
    }else if (strcmp(argv[1], "c-so") == 0)
    {

      file = fopen(argv[2], "r");
      if (file == NULL)
      {
        printf("le chemin specifier pour fichier %s  est invalide", argv[2]);
        exit(1);
      }
      if (argv[3] == NULL)
      {
        printf("Le prochain argument est absent : le SEUIL");
        exit(1);
      }
      int seuil = atoi(argv[3]);
      Image img1 = read_Image_file(argv[2]);
      Image sou = contour_filter("./filtre/sobel.txt", img1 , seuil);
      write_Image_to_file(sou, "image/sobel_simple_contour.pgm");
      printf("le fichier a ete generé dans image/sobel_simple_contour.pgm ");

      strcat(logiciel, "  image/sobel_simple_contour.pgm");
      system(logiciel);
      freeMatrice(img1.M, img1.largeur);
      freeMatrice(sou.M, sou.largeur);
      fclose(file);
      exit(0);
    }else if (strcmp("c-pre" , argv[1])==0 )
    {
      
      file = fopen(argv[2], "r");
      if (file == NULL)
      {
        printf("le chemin specifier pour fichier %s  est invalide", argv[2]);
        exit(1);
      }
      if (argv[3] == NULL)
      {
        printf("Le prochain argument est absent : le SEUIL");
        exit(1);
      }
      int seuil = atoi(argv[3]);
      Image img1 = read_Image_file(argv[2]);
      Image sou = contour_filter("./filtre/prewitt.txt", img1 , seuil);
      write_Image_to_file(sou, "image/prewitt_simple_contour.pgm");
      printf("le fichier a ete generé dans image/prewitt_simple_contour.pgm ");

      strcat(logiciel, "  image/prewitt_simple_contour.pgm");
      system(logiciel);
      freeMatrice(img1.M, img1.largeur);
      freeMatrice(sou.M, sou.largeur);
      fclose(file);
      exit(0);
    } else if (strcmp("-km", argv[1]) == 0)
      {
        file = fopen(argv[2], "r");
        if (file == NULL)
        {
        printf("le chemin specifier pour fichier %s est invalide", argv[2]);
        exit(1);
        }
        int cluster = atoi(argv[3]);
        if (cluster <= 1)
        {
          printf(" Le nombre de cluster %d doit etre strictement superieur 1 \n", cluster);
          exit(1);
        }

        Image img1 = read_Image_file(argv[2]);
        Image sou = kmeans_f_niveau_de_gris(img1, cluster);
        write_Image_to_file(sou, "image/kmeans_Niveau_de_gris.pgm");
        printf("le fichier à ete generé dans image/kmeans_Niveau_de_gris.pgm ");

        strcat(logiciel, "  image/kmeans_Niveau_de_gris.pgm");
        system(logiciel);
        freeMatrice(img1.M, img1.largeur);
        freeMatrice(sou.M, sou.largeur);
        fclose(file);
        exit(0);
      }
  else
    {
      printf("Impossible d'executer une action aucun parametre de correspond à %s" , argv[1]);
      exit(1);
    }

    
  }
  if (argc == 5)
  {
    if (strcmp("interpollation", argv[1]) == 0)
    {
      file = fopen(argv[2], "r");
      if (file == NULL)
      {
        printf("le chemin specifier pour fichier %s  est invalise", argv[2]);
        exit(1);
      }
      int x = atoi(argv[3]);
      int y = atoi(argv[4]);
      Image img1 = read_Image_file(argv[2]);
      Image sou = interpolationPlusProcheVoisin(img1, x, y);
      write_Image_to_file(sou, "image/interpollation_ppvoisin.pgm");

      strcat(logiciel, "  image/interpollation_ppvoisin.pgm");
      system(logiciel);
      freeMatrice(img1.M, img1.largeur);
      freeMatrice(sou.M, sou.largeur);
      fclose(file);
      exit(0);
    }

    else if (strcmp("transSaturation", argv[1]) == 0)
    {

      file = fopen(argv[2], "r");
      if (file == NULL)
      {
        printf("le chemin specifier pour fichier %s est invalide", argv[2]);
        exit(1);
      }
      Image img1 = read_Image_file(argv[2]);
      int smax = atoi(argv[3]);
      int smin = atoi(argv[4]);
      Image add = transformation_saturation(img1, smax, smin);
      write_Image_to_file(add, "image/transformation_saturation.pgm");

      strcat(logiciel, "  image/transformation_saturation.pgm");
      system(logiciel);
      freeMatrice(img1.M, img1.largeur);
      freeMatrice(add.M, add.largeur);
      fclose(file);
      exit(0);
    }

    else if (strcmp("transMorceauInverse", argv[1]) == 0)
    {

      file = fopen(argv[2], "r");
      if (file == NULL)
      {
        printf("le chemin specifier pour fichier %s est invalide", argv[2]);
        exit(1);
      }
      Image img1 = read_Image_file(argv[2]);
      int smax = atoi(argv[3]);
      int smin = atoi(argv[4]);
      Image add = transformation_morceau_inverse(img1, smax, smin);
      write_Image_to_file(add, "image/inverse_Morceau_transformation.pgm");

      strcat(logiciel, "  image/inverse_Morceau_transformation.pgm");
      system(logiciel);
      freeMatrice(img1.M, img1.largeur);
      freeMatrice(add.M, add.largeur);
      fclose(file);
      exit(0);
    }
    else if (strcmp("transMorceau", argv[1]) == 0)
    {

      file = fopen(argv[2], "r");
      if (file == NULL)
      {
        printf("le chemin specifier pour fichier %s est invalide", argv[2]);
        exit(1);
      }
      Image img1 = read_Image_file(argv[2]);
      int smax = atoi(argv[3]);
      int smin = atoi(argv[4]);
      Image add = transformation_morceau(img1, smax, smin);
      write_Image_to_file(add, "image/Morceau_transformation.pgm");

      strcat(logiciel, "  image/Morceau_transformation.pgm");
      system(logiciel);
      freeMatrice(img1.M, img1.largeur);
      freeMatrice(add.M, add.largeur);
      fclose(file);
      exit(0);
    }

    else if (strcmp("transMorceauInverse", argv[1]) == 0)
    {

      file = fopen(argv[2], "r");
      if (file == NULL)
      {
        printf("le chemin specifier pour fichier %s est invalide", argv[2]);
        exit(1);
      }
      Image img1 = read_Image_file(argv[2]);
      int smax = atoi(argv[3]);
      int smin = atoi(argv[4]);
      Image add = transformation_morceau_inverse(img1, smax, smin);
      write_Image_to_file(add, "image/inverse_Morceau_transformation.pgm");

      strcat(logiciel, "  image/inverse_Morceau_transformation.pgm");
      system(logiciel);
      freeMatrice(img1.M, img1.largeur);
      freeMatrice(add.M, add.largeur);
      fclose(file);
      exit(0);
    }
    else if (strcmp("transgamma", argv[1]) == 0)
    {

      file = fopen(argv[2], "r");
      if (file == NULL)
      {
        printf("le chemin specifier pour fichier %s est invalide", argv[2]);
        exit(1);
      }
      Image img1 = read_Image_file(argv[2]);
      int c = atoi(argv[3]);
      float gamma = atoi(argv[4]);
      Image add = transformation_gamma(img1, c, gamma);
      write_Image_to_file(add, "image/gamma_transformation.pgm");

      strcat(logiciel, "  image/gamma_transformation.pgm");
      system(logiciel);
      freeMatrice(img1.M, img1.largeur);
      freeMatrice(add.M, add.largeur);
      fclose(file);
      exit(0);
    }
    else if (strcmp("-c", argv[1]) == 0)
    {
      file = fopen(argv[2], "r");
      if (file == NULL)
      {
        printf("le chemin specifier pour fichier %s est invalide", argv[2]);
        exit(1);
      }
      if (strcmp("-mo", argv[3]) == 0)
      {
        Image m = read_Image_file(argv[2]);
        int rayon = atoi(argv[4]);
        if (rayon <= 0)
        {
          printf(" Le rayon %d doit etre strictement positif \n", rayon);
          exit(1);
        }

        Image m2 = convolution(m, "moyenneur", rayon);
        write_Image_to_file(m2, "./image/moyenneur_convolution_g.pgm");
        strcat(logiciel, "  ./image/moyenneur_convolution_g.pgm");
        system(logiciel);
        freeMatrice(m.M, m.largeur);
        freeMatrice(m2.M, m2.largeur);
        fclose(file);
        exit(0);
      }
      else if (strcmp("-me", argv[3]) == 0)
      {
        Image m = read_Image_file(argv[2]);
        int rayon = atoi(argv[4]);
        if (rayon <= 0)
        {
          printf(" Le rayon %d doit etre strictement positif \n", rayon);
          exit(1);
        }

        Image m2 = convolution(m, "median", rayon);
        write_Image_to_file(m2, "./image/median_convolution_g.pgm");
        strcat(logiciel, "  ./image/median_convolution_g.pgm");
        system(logiciel);
        freeMatrice(m.M, m.largeur);
        freeMatrice(m2.M, m2.largeur);
        fclose(file);
        exit(0);
      }
      else if (strcmp("-g", argv[3]) == 0)
      {
        Image m = read_Image_file(argv[2]);
        int rayon = atoi(argv[4]);
        if (rayon <= 0)
        {
          printf(" Le rayon %d doit etre strictement positif \n", rayon);
          exit(1);
        }

        Image m2 = convolution(m, "gaussien", rayon);
        write_Image_to_file(m2, "./image/gaussien_convolution_g.pgm");
        strcat(logiciel, "  ./image/gaussien_convolution_g.pgm");
        system(logiciel);
        freeMatrice(m.M, m.largeur);
        freeMatrice(m2.M, m2.largeur);
        fclose(file);
        exit(0);
      }
      else
      {
        printf("Aucune option ne matche avec votre entrée  ' %s '  \n", argv[3]);
        exit(1);
      }
    }
      else if (strcmp("-cr", argv[1]) == 0)
      {
        file = fopen(argv[2], "r");
        if (file == NULL)
        {
        printf("le chemin specifier pour fichier %s est invalide", argv[2]);
        exit(1);
        }

        Image img1 = read_Image_file(argv[2]);
        int nbgerme = atoi(argv[3]);
        int seuill = atoi(argv[4]);
        Image sou = croissance_des_regions(img1, nbgerme, seuill);
        write_Image_to_file(sou, "image/croissance_region.pgm");
        printf("le fichier à ete generé dans image/croissance_region.pgm ");

        strcat(logiciel, "  image/croissance_region.pgm");
        system(logiciel);
        freeMatrice(img1.M, img1.largeur);
        freeMatrice(sou.M, sou.largeur);
        fclose(file);
        exit(0);
       }
   else
    {
      printf("Impossible d'executer une action aucun parametre de correspond à %s" , argv[1]);
      exit(1);
    }
  } else
    {
      printf("Impossible d'executer une action aucun parametre de correspond à %s" , argv[1]);
      exit(1);
    }
    return 0;
 }
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
  printf("\nfichier 1 , %s\n", argv[3]);
  char logiciel[10] = "eog";
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
    }else if (strcmp("otsu" , argv[1]) == 0)
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
      printf("ok");
      exit(1);
    }
  }
  else if (argc == 4)
  {
    char visio[10] = "eog";
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

      strcat(visio, "  image/addition_image.pgm");
      system(visio);
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

      strcat(visio, "  image/soustraction_image.pgm");
      system(visio);
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

      strcat(visio, "  image/multiplication_image_ratio.pgm");
      system(visio);
      freeMatrice(img1.M, img1.largeur);
      freeMatrice(sou.M, sou.largeur);
      fclose(file);
      exit(0);
    }else if (strcmp("binarisation" , argv[1]) == 0 )
    {
      
      file = fopen(argv[2], "r");
      if (file == NULL )
      {
        printf("le chemin specifier pour fichier %s est invalide", argv[2]);
        exit(1);
      }
      Image img1 = read_Image_file(argv[2]);
      int seuil = atoi(argv[3]);
      Image add = binarisation(img1 , seuil);
      write_Image_to_file(add, "image/binarisation_image.pgm");

      strcat(visio, "  image/binarisation_image.pgm");
      system(visio);
      freeMatrice(img1.M, img1.largeur);
      freeMatrice(add.M, add.largeur);
      fclose(file);
      exit(0);
    }

    
  }
if (argc ==  5)
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
      Image sou = interpolationPlusProcheVoisin(img1 , x ,y);
      write_Image_to_file(sou, "image/interpollation_ppvoisin.pgm");

      strcat(logiciel, "  image/interpollation_ppvoisin.pgm");
      system(logiciel);
      freeMatrice(img1.M, img1.largeur);
      freeMatrice(sou.M, sou.largeur);
      fclose(file);
      exit(0);
    }

    else if (strcmp("transSaturation" , argv[1]) == 0 )
    {
      
      file = fopen(argv[2], "r");
      if (file == NULL )
      {
        printf("le chemin specifier pour fichier %s est invalide", argv[2]);
        exit(1);
      }
      Image img1 = read_Image_file(argv[2]);
      int smax = atoi(argv[3]);
      int smin = atoi(argv[4]);
      Image add = transformation_saturation(img1 ,smax , smin);
      write_Image_to_file(add, "image/transformation_saturation.pgm");

      strcat(logiciel, "  image/transformation_saturation.pgm");
      system(logiciel);
      freeMatrice(img1.M, img1.largeur);
      freeMatrice(add.M, add.largeur);
      fclose(file);
      exit(0);
    }

    else if (strcmp("transMorceauInverse" , argv[1]) == 0 )
    {
      
      file = fopen(argv[2], "r");
      if (file == NULL )
      {
        printf("le chemin specifier pour fichier %s est invalide", argv[2]);
        exit(1);
      }
      Image img1 = read_Image_file(argv[2]);
      int smax = atoi(argv[3]);
      int smin = atoi(argv[4]);
      Image add = transformation_morceau_inverse(img1 ,smax , smin);
      write_Image_to_file(add, "image/inverse_Morceau_transformation.pgm");

      strcat(logiciel, "  image/inverse_Morceau_transformation.pgm");
      system(logiciel);
      freeMatrice(img1.M, img1.largeur);
      freeMatrice(add.M, add.largeur);
      fclose(file);
      exit(0);
    } else if (strcmp("transMorceau" , argv[1]) == 0 )
    {
      
      file = fopen(argv[2], "r");
      if (file == NULL )
      {
        printf("le chemin specifier pour fichier %s est invalide", argv[2]);
        exit(1);
      }
      Image img1 = read_Image_file(argv[2]);
      int smax = atoi(argv[3]);
      int smin = atoi(argv[4]);
      Image add = transformation_morceau(img1 ,smax , smin);
      write_Image_to_file(add, "image/Morceau_transformation.pgm");

      strcat(logiciel, "  image/Morceau_transformation.pgm");
      system(logiciel);
      freeMatrice(img1.M, img1.largeur);
      freeMatrice(add.M, add.largeur);
      fclose(file);
      exit(0);
    }

    else if (strcmp("transMorceauInverse" , argv[1]) == 0 )
    {
      
      file = fopen(argv[2], "r");
      if (file == NULL )
      {
        printf("le chemin specifier pour fichier %s est invalide", argv[2]);
        exit(1);
      }
      Image img1 = read_Image_file(argv[2]);
      int smax = atoi(argv[3]);
      int smin = atoi(argv[4]);
      Image add = transformation_morceau_inverse(img1 ,smax , smin);
      write_Image_to_file(add, "image/inverse_Morceau_transformation.pgm");

      strcat(logiciel, "  image/inverse_Morceau_transformation.pgm");
      system(logiciel);
      freeMatrice(img1.M, img1.largeur);
      freeMatrice(add.M, add.largeur);
      fclose(file);
      exit(0);
    } else if (strcmp("transgamma" , argv[1]) == 0 )
    {
      
      file = fopen(argv[2], "r");
      if (file == NULL )
      {
        printf("le chemin specifier pour fichier %s est invalide", argv[2]);
        exit(1);
      }
      Image img1 = read_Image_file(argv[2]);
      int c = atoi(argv[3]);
      float gamma = atoi(argv[4]);
      Image add = transformation_gamma(img1 ,c , gamma);
      write_Image_to_file(add, "image/gamma_transformation.pgm");

      strcat(logiciel, "  image/gamma_transformation.pgm");
      system(logiciel);
      freeMatrice(img1.M, img1.largeur);
      freeMatrice(add.M, add.largeur);
      fclose(file);
      exit(0);
    }

    
}
 

  //  struct Image img = read_Image_file("/home/herman/Documents/Cours/Master1/Semestre 2/Vision ordinateur/computer vision/image/contour/Fig2.pgm");
  //contour(img , "sobel" , 25);
  // Image m =  contour_filtersansSeuil("./filtre/sobel.txt" , img);
  // write_Image_to_file(m , "sobel.pgm");
  /*
 struct Image img = read_Image_file("./image/traitement/original/addition1.pgm");
struct Image img2 = read_Image_file("./image/traitement/original/addition2.pgm");
 struct Image img3 = read_Image_file("./image/traitement/original/addimg.pgm");
 struct Image img4 = read_Image_file("./image/traitement/original/mul2.pgm");
*/
  // struct Image img1 = read_Image_file("./image/cours/original/petitcoinOu.pgm");

  // struct Image img1 = read_Image_file("./image/convolution/Fig3.pgm");
  //struct Image img_transpose =transpose_Image(img );
  //write_Image_to_file(img_transpose , "./Image/Image_transpose.pgm");
  //Image img_transformation_lineaire =transformation_lineaire(img ,100 , 20);
  // Image add = addition(img , img1);
  // write_Image_to_file(add , "./image/cours/addition2.pgm");
  /*Image sous = soustration(img , img_transformation_lineaire);
  write_Image_to_file(sous , "./image/soustration.pgm");
   Image mul = multiplication(img ,1.5);
  write_Image_to_file(mul , "./image/mutiplication.pgm");
  
  Image img_transformation_sa =transformation_saturation(img ,255,0,100 , 40);
    write_Image_to_file(img_transformation_sa , "./image/saturation.pgm");
    */
  //Image egali = egalisation_histogramme(img);
  //  write_Image_to_file(egali , "./image/egalisation_obscure.pgm");
  /*
int i =0 ;
int j=0;
   struct Image imgpbm = read_pbm_file("./image/binaire.pbm");
  write_Image_to_file_Pbm(imgpbm , "./image/testPbm.pbm");
  */

  // Image binar  = binarisation(img1 , 20);
  //write_Image_to_file_Pbm(binar , "./image/binarisation.pbm");

  //struct Image img_ne =negatif_image(img1);
  //write_Image_to_file(img_ne , "./image/inversion.pgm");
  //struct Image im = filter_with_mean(img1 , 2);
  //Image im =convolution(img1 ,"moyenneur", 1);
  //write_Image_to_file(im , "./image/convolution/moyenneur.pgm");

  //printf("Luminance %f" ,luminance(img1));
  //printf("Contraste %f" ,contraste(img1));

  //int tab[14] = {15,78,21,98,23,82,32,12,7,14 ,0,1,7};
  //findMedianWithBubbleSort(tab , 14);
  //Image im = convolution(img1 ,"gaussien", 1);
  //write_Image_to_file(im ,"./image/convolution/gaussien2.pgm");
  /* printf("work\n");
 Image m = derive(img1 , 25);
 write_Image_to_file(m , "./image/contour/derivee.pgm");
 write_Image_to_file(laplacien(img1 ,100) , "./image/contour/laplacien.pgm");
Image prew = contour_with_Prewitt(img1 );
 write_Image_to_file(prew, "./image/contour/prewitt.pgm");
 Image robert = contour_with_Roberts(img1);
 write_Image_to_file(robert, "./image/contour/roberts.pgm");

  Image soble = contour_with_sobel(img1);
 write_Image_to_file(soble, "./image/contour/sobel.pgm");
 */
  /* Image m = read_Image_file("./image/cours/transLinear.pgm");
  //Image m2 = luminanceImage(m);
  //Image m2 = contrasteImage(m);
 // write_Image_to_file(m2 ,"./image/cours/constrate.pgm" );
  //histogramme(m);
printf("%d\n" , findMinPixelValueInM(m));
printf("%d\n" , findMaxPixelValueInM(m));
Image m2 = transformation_lineaire(m);
  write_Image_to_file(m2 ,"./image/cours/transformationLineaire.pgm" );
Image m3 = transformation_saturation(m , 150 ,40);
  write_Image_to_file(m3 ,"./image/cours/transformationSaturation.pgm" );
  
 */

  /*
Image im = interpolationPlusProcheVoisin( img , 50 , 50);
 write_Image_to_file(im ,"./image/plusprochevoisin.pgm");
 freeMatrice(im.M , im.largeur);
  struct Image ms = read_Image_file("./image/cours/original/barbara.pgm");
  Image  m = transformation_morceau(ms, 140, 70);
      write_Image_to_file(m ,"./image/cours/transformationmorceau.pgm" );
      freeMatrice(m.M , m.largeur);

  Image  ma = transformation_morceau(ms, 180, 50);
      write_Image_to_file(ma ,"./image/cours/transformationmorceau_inverse.pgm" );
      freeMatrice(ma.M , ma.largeur);

    ma = transformation_gamma(img , 100 , 50);
      write_Image_to_file(ma ,"./image/cours/albert_gamma.pgm" );
      freeMatrice(ma.M , ma.largeur);
*/
  /*
Image b = seuillage_historgramme(img);
Image b1 = seuillage_historgramme(img2);
Image r1 = and(b ,b1);
write_Image_to_file_Pbm(r1 ,"./image/cours/et.pgm");
write_Image_to_file_Pbm(b ,"./image/cours/seuillageET.pgm");
write_Image_to_file_Pbm(b1 ,"./image/cours/seuillageOU.pgm");

   freeMatrice(r1.M , r1.largeur);
*/

  /*Image  r2= or(b ,b1);
Image r3 = xor(b ,b1);

write_Image_to_file_Pbm(r2 ,"./image/cours/ou.pgm");
write_Image_to_file_Pbm(r3 ,"./image/cours/xor.pgm");
 freeMatrice(b.M , b.largeur);
  freeMatrice(b1.M , b1.largeur);
   freeMatrice(r1.M , r1.largeur);
    freeMatrice(r2.M , r2.largeur);
     freeMatrice(r3.M , r3.largeur);*/

  //read_filter("./filtre/filtre1.txt");
  //   Image m1 = derive(img2 , 15) ;
  // write_Image_to_file(m1, "./image/contour/derive.pgm");
  //    write_Image_to_file(laplacien(img , 15) , "./image/contour/laplacien.pgm");
  // contour(img , "prewitt" , 60);
  //  histogramme(img2);
  // binarisation(img2 ,188);
  //kmeans(img ,10 , 2,200);
  /* Image s = addition(img3 , img3);
  Image m = multiplication(img4 ,1.2);
    write_Image_to_file(m, "./image/traitement/multiplication_elem.pgm");
    */
  return 0;
}
#include <stdio.h>
#include <stdlib.h>

#include "./Header/Contour.h"

int main(void)
{
  char path[100];
  char *choix_menu;
  unsigned int incorrect = 1;
  printf("************************************ Bienvenue sur notre application de Traitement d'image ************************************\n");
  printf("****************Chapitre 02-Traitement de base****************\n\n");
  printf("****************Chapitre 03-Convolution****************\n\n");
  printf("****************Chapitre 04-Transdormee de fourier****************\n\n");
  printf("****************Chapitre 05-Contours****************\n\n");
  printf("****************Chapitre 06-Segmentation****************\n\n");
  printf("****************Chapitre 07-Images_binaires****************\n\n");
  printf("****************Chapitre 08-Detection-Reconnaissance-2D****************\n\n");

  printf("**********Faites votre choix***************** \n");
    scanf("%s", choix_menu);
  do
  { 
    if ( choix_menu <= 1 || choix_menu > 8)
    {
      printf("choix incorrect ! Veuillez  reessayer \t");
          scanf("%s", choix_menu);

    }
    else
    {
      printf("bon choix");
      incorrect = 0;
    }

  } while (incorrect ==1);

  /*   
    printf("*****************Entrer le chemin de l'image ******************************\n");
  //  scanf("%s" , path) ;
      Image img = read_Image_file("./image/obscure.pgm");
      Image lena = read_Image_file("./image/lena.pgm");
      Image Lum_const = read_Image_file("./image/cours/img1.pgm");

//transposition de l'image
      Image img_transpose =transpose_Image(img);
      write_Image_to_file(img_transpose , "./image/cours/transposeoscure.pgm");
      freeMatrice(img_transpose.M , img_transpose.largeur);

 Image m = read_Image_file("./image/cours/transLinear.pgm");

// transformation lineaire avec  saturation     
      Image m2 = transformation_lineaire(m);
       write_Image_to_file(m2 ,"./image/cours/transformationLineaireok.pgm" );
      freeMatrice(m2.M , m2.largeur);

      Image m3 = transformation_saturation(m , 150 ,40);
      write_Image_to_file(m3 ,"./image/cours/transformationSaturation.pgm" );
      freeMatrice(m3.M , m3.largeur);


// Egalisation de l'histogramme

Image egali = egalisation_histogramme(img);
    write_Image_to_file(egali , "./image/cours/egalisation_obscure.pgm");
      freeMatrice(egali.M , m3.largeur);


// Negatif de l'image m[i][j]-255
Image negatif = negatif_image(lena);
    write_Image_to_file(negatif , "./image/cours/negatif.pgm");
      freeMatrice(negatif.M , m3.largeur);



// Amelioration de la luminance de l'image

Image lum = luminanceImage(Lum_const);
    write_Image_to_file(lum , "./image/cours/luminance.pgm");
      freeMatrice(lum.M , lum.largeur);
     

// Amelioration du contraste  de l'image

Image constr = contrasteImage(Lum_const);
    write_Image_to_file(constr , "./image/cours/constrate.pgm");
      freeMatrice(constr.M , constr.largeur);
     
*/

  return 0;
}
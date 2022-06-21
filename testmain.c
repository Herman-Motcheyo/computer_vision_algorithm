

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./Header/Contour.h"
#include "./Header/Segmentation.h"

int main(int argc, char const *argv[])
{
    char logiciel[10] = "eog";
     Image m = read_Image_file("./image/imgsource/lena.pgm");
     Image m2 = croissance_des_regions(m, 2 , 10);
write_Image_to_file(m2 , "croissance.pgm");
    //  histogramme(m);
        // Image m2 = seuillageAutomatique(m);
        // write_Image_to_file_Pbm(m2 , "test.pbm");
  //      Image m3 = binarisation(m , 129);
     //   write_Image_to_file_Pbm(m3 , "testb.pbm");

  //   int a =histogram_otsu(m.largeur,m.hauteur , m);
//printf("la valeur du seuil %d" , a);
     // Image s = seuillageAutomatique(m);
      //write_Image_to_file_Pbm(s, "auto.pbm");
 strcat(logiciel, "  croissance.pgm");
  float * tab ;
  int n = 0;
  printf("entrer la valeur de n \t");
  //scanf("%d" ,&n);
  //tab = calloc(n, sizeof(float));
  //for (size_t i = 0; i < n; i++)
  //{
   //   scanf("%f",&tab[i]);
  //}
  

system(logiciel);
    return 0;
}

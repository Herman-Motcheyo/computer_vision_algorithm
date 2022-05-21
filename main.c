#include <stdio.h>
#include <stdlib.h>



#include "./Header/Contour.h"

int main(void){
 struct Image img = read_Image_file("./image/obscure.pgm");
  struct Image img1 = read_Image_file("./image/convolution/Fig3.pgm");
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
 Image im = convolution(img1 ,"gaussien", 1);
 write_Image_to_file(im ,"./image/convolution/gaussien2.pgm");
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
 */   return 0;
}
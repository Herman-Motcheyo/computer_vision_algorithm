#include <stdio.h>
#include <stdlib.h>

#include "../Header/Operations.h"

int main(void){
 struct Image img = read_Image_file("./image/trello.pgm");
 //struct Image img_transpose =transpose_Image(img );
 //write_Image_to_file(img_transpose , "./Image/Image_transpose.pgm");
//Image img_transformation_lineaire =transformation_lineaire(img ,100 , 20);
/* Image add = addition(img , img);
  write_Image_to_file(add , "./image/addition.pgm");
 Image sous = soustration(img , img_transformation_lineaire);
  write_Image_to_file(sous , "./image/soustration.pgm");
   Image mul = multiplication(img ,1.5);
  write_Image_to_file(mul , "./image/mutiplication.pgm");
  */
  Image img_transformation_sa =transformation_saturation(img ,255,0,100 , 40);
    write_Image_to_file(img_transformation_sa , "./image/saturation.pgm");
    return 0;
}
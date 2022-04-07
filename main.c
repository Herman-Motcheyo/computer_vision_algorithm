#include <stdio.h>
#include <stdlib.h>

#include "../Header/Operations.h"

int main(void){
 struct image img = read_image_file("./image/trello.pgm");
 //struct image img_transpose =transpose_image(img );
 //write_image_to_file(img_transpose , "./image/image_transpose.pgm");
 image img_transformation_lineaire =transformation_lineaire(img ,150 ,50 );
  write_image_to_file(img_transformation_lineaire , "./image/transformation_lineaire.pgm");

    return 0;
}
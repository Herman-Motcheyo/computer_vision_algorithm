#include <stdio.h>
#include <stdlib.h>

#include "../Header/Operations.h"

int main(void){
 struct image img = read_image_file("./image/trello.pgm");
 struct image img_transpose =transpose_image(img );
 write_image_to_file(img_transpose , "./image/image_transpose.pgm");
    return 0;
}
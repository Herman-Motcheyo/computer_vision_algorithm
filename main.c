#include <stdio.h>
#include <stdlib.h>

#include "../Header/Operations.h"

int main(void){
 struct image img = read_image_file("./image/trm.pgm");
 write_to_image_file(img , "./image/tet.pgm");
    return 0;
}
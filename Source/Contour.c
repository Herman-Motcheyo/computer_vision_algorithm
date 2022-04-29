#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Header/Contour.h"

Image contour_with_sobel(Image m)
{
    float **sobel = initialise_filtre(1);
    sobel[0][0] = -1;
     sobel[0][1] = 0;
      sobel[0][2] = 1;
       sobel[1][0] = -2;
        sobel[1][1] = 0;
         sobel[1][2] = 2;
          sobel[2][0] = -1;
           sobel[2][1] = 0;
            sobel[2][2] = 1;

    m.M = convolveMult(m.M, sobel, m.largeur, m.hauteur, 1, m.MAX_PIXEL_VALUE);

    freeFilter(sobel , 3);
    return m;
}
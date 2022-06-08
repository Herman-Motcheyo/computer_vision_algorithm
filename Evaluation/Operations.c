#include <stdio.h>
#include <stdlib.h>
#include "string.h"


#include "./Header/Contour.h"
#include "./Header/Segmentation.h"

int main(int argc, char  *argv[])
{
  if (argc == 3)
  {
     if (strcmp(argv[2] , "histogramme" ) )
     {

        Image m_his = read_Image_file("");
       // histogramme(m_his);
        freeMatrice(m_his.M , m_his.largeur );
     }
     
  }
  
  return 0;
}

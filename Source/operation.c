

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HEIGHT 3000
#define MAX_WIDTH 3000

int image[MAX_HEIGHT][MAX_WIDTH];
int MAX_PIXEL_VALUE;
int width = 0;
int height = 0;

void read_image_file(char *path)
{
    char pgm_name[20];
    int hauteur = 0;
    int largeur = 0;
    FILE *file = NULL;
    file = fopen(path, "r");
    char empty_text[200];
    int i, j, value = 0;
    if (file != NULL)
    {
        fgets(pgm_name, 20, file);
        printf("%s\n", pgm_name);
        if (strcmp(pgm_name, "P2\n") == 0)
        {
            fgets(empty_text, 200, file);
            fscanf(file, "%d", &height);
            fscanf(file, "%d", &width);
            fscanf(file, "%d", &MAX_PIXEL_VALUE);
            printf("le nombre max est %d \n" , MAX_PIXEL_VALUE);

            for (i = 0; i < width; i++)
            {
                for (j = 0; j < height; j++)
                {
                    fscanf(file, "%d", &image[i][j]);
                }
            }
        }
      fclose(file);
    }
    else
    {
        printf("impossible de lire le fichier de l'image ou chemin incorrect");
    }
}

void histogramme(char * path){
    int i,j = 0;
    int h[MAX_PIXEL_VALUE];
    read_image_file("path");
    for ( i = 0; i <= MAX_PIXEL_VALUE; i++) h[i]  = 0 ;
    
    for ( i = 0; i < width; i++)
    {
        for ( j = 0; j < height; j++)
        {
            h[image[i][j]]++;
        }
        
    }
    

}

void transformation_lineaire(char *path){
        read_image_file(path);

}




void write_to_file_image( int **m ,int width , int height, char *path ){
    FILE *file_write = NULL;
    file_write = fopen(path ,"a");
     int i,j =0;
    if (file_write != NULL)
    {
        fprintf(file_write , "%s\n" ,"P2" );
        fprintf(file_write , "%s\n" ,"# Herman motcheyo");
        fprintf(file_write ,"%d " ,height);
        fprintf(file_write ,"%d\n" ,width);
        fprintf(file_write ,"%d\n" ,MAX_PIXEL_VALUE);
         for (i = 0; i < width; i++)
            {
                for (j = 0; j < height; j++)
                {
                    fprintf(file_write ,"%d\n" ,m[i][j]);
                }
            }

            fclose(file_write);

    }else{
        printf("erreur impossible d'ouvrir le fichier d'affichage de l'image");
    }
    

}

void transpose(char *path){

    read_image_file(path);
    int i,j = 0;
    int **m_trans = calloc(height , sizeof(int*)) ;
    // m_trans = calloc(width ,sizeof(int*));

    for ( i = 0; i < height; i++)
    {
       m_trans[i] = calloc(width , sizeof(int));
    }
    
  for ( i = 0; i < width; i++)
    {
        for ( j = 0; j < height; j++)
        {
            m_trans[j][i] =image[i][j];
        }
        
    }

    write_to_file_image(m_trans ,height , width , "../image/transpose.pgm");

}
int main(void)
{

    read_image_file("../image/trm.pgm");
    transpose("../image/trm.pgm");
    return 0;
}
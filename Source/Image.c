#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Header/Image.h"
/*    
**  this function is used to generate matrix 
*/

int **generate_matrice(int nb_line, int nb_column)
{
    int i = 0;
    int **M = calloc(nb_line, sizeof(int *));
    for (i = 0; i < nb_line; i++)
    {
        M[i] = calloc(nb_column, sizeof(int));
    }
    return M;
}

Image read_pbm_file(char* path){
    
     struct Image img;

    FILE *file = NULL;
    file = fopen(path, "r");
    int i = 0, j = 0;
    char name[20], description[200];
    img.MAX_PIXEL_VALUE=1;
    if (file != NULL)
    {
        fgets(name, 20, file);
        strcpy(img.name, name);
        if (strcmp(img.name, "P1\n") == 0)
        {
            fgets(description, 200, file);
            strcpy(img.description, description);
            fscanf(file, "%d", &img.hauteur);
            fscanf(file, "%d", &img.largeur);
            img.M = generate_matrice(img.largeur, img.hauteur);
            for (i = 0; i < img.largeur; i++)
            {    
                for (j = 0; j < img.hauteur; j++)
                {
                    fscanf(file, "%d\n", &img.M[i][j]);
                   // printf("%d" ,img.M[i][j] );
                }
            }
        }
        fclose(file);
        return img;
    }
    else
    {
        printf("impossible de lire le fichier de l'Image ou chemin incorrect");
        return img;
    }
}

void write_Image_to_file_Pbm(struct Image img, char* path){
  FILE *file_write = NULL;
    file_write = fopen(path, "a");
    int i, j = 0;
    if (file_write != NULL)
    {
        fprintf(file_write, "%s\n", img.name);
        fprintf(file_write, "%s\n", img.description);
        fprintf(file_write, "%d ", img.hauteur);
        fprintf(file_write, "%d\n", img.largeur);
        for (i = 0; i < img.largeur; i++)
        {
            for (j = 0; j < img.hauteur; j++)
            {
                fprintf(file_write, "%d", img.M[i][j]);
            }
        }

        fclose(file_write);
    }
    else
    {
        printf("erreur impossible d'ouvrir le fichier d'affichage de l'Image");
    }
}
#ifndef OPERATIONS_H
#define OPERATIONS_H

int** generate_matrice(int nb_line,int nb_column);
struct image read_image_file(char *path);
void write_to_image_file(  struct image img , char *path );
void transpose_image(struct image , char *path);

typedef struct image
{
    char name[20];
    int hauteur ;
    int largeur ;
    int MAX_PIXEL_VALUE ;
    char description[200];
    int **M ;
} image;

#endif
#ifndef OPERATIONS_H
#define OPERATIONS_H

int** generate_matrice(int nb_line,int nb_column);
struct image read_image_file(char *path);
void write_image_to_file(  struct image img , char *path );
struct image transpose_image(struct image);

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
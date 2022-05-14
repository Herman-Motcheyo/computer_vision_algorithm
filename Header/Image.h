#ifndef IMAGE_H
#define IMAGE_H

typedef struct Image
{
    char name[20];
    int hauteur;
    int largeur;
    int MAX_PIXEL_VALUE;
    char description[200];
    int **M;
} Image;

Image create_image(Image m);

int **generate_matrice(int nb_line, int nb_column);
void freeMatrice(int **m, int nb_line);

//la luminance est definie la moyenne de tous les pixels de l'image
float luminance(Image m);

//le contraste peut aussi etre defini comme l'ecart type  des variations des niveaux de gris
float contraste(Image m);
//lecture image binaire
Image read_pbm_file(char *path);
void write_Image_to_file_Pbm(struct Image, char *);
Image lecturePpm(char *path); //lecture image couleur

#endif

typedef struct Image
{
    char name[20];
    int hauteur;
    int largeur;
    int MAX_PIXEL_VALUE;
    char description[200];
    int **M;
} Image;

int **generate_matrice(int nb_line, int nb_column);
void freeMatrice(int **m, int nb_line);
//lecture image binaire
Image read_pbm_file(char *path);
void write_Image_to_file_Pbm(struct Image, char *);
Image lecturePpm(char *path); //lecture image couleur
# computer_vision_algorithm

## OPERATION DE BASE SUR LES IMAGES
## 1-Pour obtenir l'HISTOGRAMME
  ** ./algo histogramme chemin_image

## 2-Pour obtenir l'EGALISATION de l'histogramme
  ** ./algo egalisation chemin_image

## 3-Pour obtenir la TRANSPOSE de l'image
  ** ./algo transpose chemin_image

## 4-Pour obtenir la TRANSFORMATION LINEAIRE d'une image 
  ** ./algo  trans_lineaire chemin_de_image

## 5-Pour obtenir l 'INVERSE de l'image 255-M[i][j]
  ** ./algo inverse chemin_de_image

## 6-Pour obtenir la LUMINANCE de l'image 
  ** ./algo luminance chemin_image

## 7-Pour obtenir le CONTRASTE de l'image 
  ** ./algo constraste chemin_image

## 8-Pour  faire l'ADDITION de 2 images 
  ** ./algo addition chemin_image1 chemin_image2

## 9-Pour  faire la SOUSTRACTION de 2 images 
  ** ./algo soustraction chemin_image1 chemin_imag

## 10-Pour  faire la MULTIPLICATION d'une image par un ratio 
  ** ./algo multiplication chemin_image valeur_ratio

## 11-Pour faire le SEUILLAGE en utilisant la METHODE de OTSU
  ** ./algo otsu chemin_image 

## 12-Pour effectuer le ZOOM avec la méthode de  L'INTERPOLLATION DES PLUS PROCHE VOISIN

  ** ./algo interpollation x y

## 13- BINARISATION
  ** ./algo binarisation chemin_de_image  seuil

## 14- TRANSFORMATION LINEAIRE AVEC SATURATION
  ** ./algo transSaturation chemin_de_image smax smin

Les pixels entre smax et smin sont mise à 255 et le reste est  inchangés
## 15- TRANSFORMATION LINEAIRE PAR MORCEAU
   ** ./algo transMorceau chemin_de_image smax smin

Les pixels entre smax et smin sont restés inchanger et le reste est mis à 255
## 15- TRANSFORMATION LINEAIRE PAR MORCEAU  INVERSE
   ** ./algo transMorceauInverse chemin_de_image smax smin

## 16- TRANSFORMATION GAMMA
      [c]: entier
      [gamma] : float  dans [1.1 , 3]
      Il faut jouer sur les valeurs de C et gamma pour obtenir une meilleur amelioration du contraste
   ** ./algo transgamma chemin_de_image c gamma

## OPERATION BOOLEAN
Méthode : à partir d'un seuillage automatique de otsu , je fais une binarisation une binarisation du
          PGM en PBM ensuite j'applique les operations logiques
## 17- AND (ET LOGIQUE) 
  ** ./algo and chemin_de_image1 chemin_de_image2

## 18- OR (OU LOGIQUE) 
  ** ./algo or chemin_de_image1 chemin_de_image2

## 19- NOT (Non LOGIQUE) 
  ** ./algo not chemin_de_image1 

## 20- XOR (XOR LOGIQUE) 
  ** ./algo xor chemin_de_image1 chemin_de_image2

## CONVOLUTION
  ## - FILTRE PASSE BAS SANS PRECISION DU FILTRE
            [-c] : convolution 
      ## 21 - FILTRE MEDIAN
          ./algo -c chemin_image -me rayon
            [-me] : median
      
      ## 22 - FILTRE MOYENNEUR
         ./algo -c chemin_image -mo rayon
            [-mo] : moyenneur
      
      ## 23 - FILTRE GUASSIEN
          ./algo -c chemin_image -g rayon
            [-g] : gaussien
  
  ##-  FILTRE PASSE BAS AVEC PRECISION DU FILTRE
      ## 24 - Convolution avec filtre en entrée
          ./algo -c chemin_image chemin_filtre
            [chemin_image] : represente le chemin absolu ou relatif de votre image sans espace
            [chemin_filtre] : représente le chemin du filtre
          FORMAT DU FICHIER CONTENANT LE FILTRE
          ---Ligne 1 : reprensente le rayon du filtre
          ---Ligne 2 : reprensente le facteur de normalisation du filtre
          --- reste de ligne construisions de la matrice
          exple
          1
          9
          1 1 1
          1 1 1 
          1 1 1
          ou encore
          2
          167
          1 2 3 4 5
          2 3 5 1 9
          9 7 8 6 3
          2 2 7 9 6
          0 9 0 6 4
    Dans cet premier menu , je génere le filtre de maniere automatique
            -g : pour gaussien . Ce filtre est généré à apartir de la fonction
             gaussienne . ET tous les pixels sont normalisés
            -mo : tous les pixels sont à 1 et normalisés . C'est 1/taille du filtre . exple 1/3*3


##  SEGMENTATION DES IMAGES À NIVEAUX DE GRIS ET PNM 
  ## APPROCHE PAR SEUILLAGE
  #### 25-ALGORITHME  OTSU
    ** ./algo otsu chemin_image 
              [chemin_image] : represente le chemin absolu ou relatif de votre image sans espace
  
  ## APPROCHE PAR REGION
    ### 26- CROISSANCE DES REGIONS
    ** ./algo -cr chemin_image nb_germe seuil
              [-cr] : Pour la croissance des regions
              [nb_germe] : pour donner le nombre de germes
              [seui] : seuil pour etablir le critère d'homogenité entre les  regions
    ### 27- KMEANS
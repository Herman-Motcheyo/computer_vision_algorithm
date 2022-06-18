# computer_vision_algorithm

## 1-Pour obtenir l'HISTOGRAMME
  ### ./algo histogramme chemin_image

## 2-Pour obtenir l'EGALISATION de l'histogramme
  ### ./algo egalisation chemin_image

## 3-Pour obtenir la TRANSPOSE de l'image
  ### ./algo transpose chemin_image

## 4-Pour obtenir la TRANSFORMATION LINEAIRE d'une image 
  ### ./algo  trans_lineaire chemin_de_image

## 5-Pour obtenir l 'INVERSE de l'image 255-M[i][j]
  ### ./algo inverse chemin_de_image

## 6-Pour obtenir la LUMINANCE de l'image 
  ### ./algo luminance chemin_image

## 7-Pour obtenir le CONTRASTE de l'image 
  ### ./algo constraste chemin_image

## 8-Pour  faire l'ADDITION de 2 images 
  ### ./algo addition chemin_image1 chemin_image2

## 9-Pour  faire la SOUSTRACTION de 2 images 
  ### ./algo soustraction chemin_image1 chemin_imag

## 10-Pour  faire la MULTIPLICATION d'une image par un ratio 
  ### ./algo multiplication chemin_image valeur_ratio

## 11-Pour faire le SEUILLAGE en utilisant la METHODE de OTSU
  ### ./algo otsu chemin_image 

## 12-Pour effectuer le ZOOM avec la méthode de  L'INTERPOLLATION DES PLUS PROCHE VOISIN

  ### ./algo interpollation x y

## 13- BINARISATION
  ### ./algo binarisation chemin_de_image  seuil

## 14- TRANSFORMATION LINEAIRE AVEC SATURATION
  ### ./algo transSaturation chemin_de_image smax smin

Les pixels entre smax et smin sont mise à 255 et le reste est  inchangés
## 15- TRANSFORMATION LINEAIRE PAR MORCEAU
   ### ./algo transMorceau chemin_de_image smax smin

Les pixels entre smax et smin sont restés inchanger et le reste est mis à 255
## 15- TRANSFORMATION LINEAIRE PAR MORCEAU  INVERSE
   ### ./algo transMorceauInverse chemin_de_image smax smin

## 16- TRANSFORMATION GAMMA
      c:entier
      gamma : float  [1.1 , 3]
      Il faut jouer sur les valeurs de C et gamma pour obtenir une meilleur amelioration du contraste
   ### ./algo transgamma chemin_de_image c gamma

## OPERATION BOOLEAN
Méthode : à partir d'un seuillage automatique de otsu , je fais une binarisation une binarisation du
          PGM en PBM ensuite j'applique les operations logiques
## 17- AND (ET LOGIQUE) 
  ### ./algo and chemin_de_image1 chemin_de_image2

## 18- OR (OU LOGIQUE) 
  ### ./algo or chemin_de_image1 chemin_de_image2

## 19- NOT (Non LOGIQUE) 
  ### ./algo not chemin_de_image1 

## 20- XOR (XOR LOGIQUE) 
  ### ./algo xor chemin_de_image1 chemin_de_image2
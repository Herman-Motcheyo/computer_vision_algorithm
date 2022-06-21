CC = gcc
CFLAGS = -Wall
LDFLAGS   =  -I 
 path_src = ./Source/Operations.c ./Source/Image.c ./Source/Convolution.c ./Source/Contour.c  ./Source/Segmentation.c
 path_src_data = ./datastructure/source/LinkedList.c ./datastructure/source/Point.c  ./datastructure/source/stack.c
 path_src_kmeans =  ./kmean/kmeans.c  ./kmean/Util.c
LDFLAGS2 = -lm

traitement_image:  $(path_src) 
	$(CC) -o algo $(CFLAGS) main.c  $(path_src) $(path_src_data)  $(LDFLAGS) ./Header/ $(LDFLAGS) ./datastructure/header/  $(LDFLAGS2) 
	$(CC) -o kmeans $(CFLAGS) $(path_src_kmeans)  $(LDFLAGS2)
run:
	./algo

clean:
	rm algo
	clear

help:
	cat README.md
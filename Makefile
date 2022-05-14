traitement_image:  ./Source/Operations.c ./Source/Image.c ./Source/Convolution.c ./Source/Contour.c   Header/Contour.h
	gcc -o traitement_image -Wall mainb.c  ./Source/Operations.c ./Source/Image.c ./Source/Convolution.c ./Source/Contour.c   ./Header/Contour.h  -I. -lm
run:
	./traitement_image
clean:
	rm traitement_image
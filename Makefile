traitement_image:  ./Source/Operations.c ./Source/Image.c ./Source/Convolution.c ./Source/Contour.c   Header/Contour.h
	gcc -o algo -Wall main.c  ./Source/Operations.c ./Source/Image.c ./Source/Convolution.c ./Source/Contour.c   ./Header/Contour.h  -I. -lm
run:
	./algo
clean:
	rm algo
	clean
traitement_image:  ./Source/Operations.c ./Source/Image.c ./Source/Convolution.c ./Source/Contour.c   Header/Contour.h
	gcc -o algo -Wall testmain.c  ./Source/Operations.c ./Source/Image.c ./Source/Convolution.c ./Source/Contour.c  ./Source/Segmentation.c -I ./Header/  -lm
run:
	./algo
clean:
	rm algo
	clear
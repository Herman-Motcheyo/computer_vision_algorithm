test:  ./Source/Operations.c ./Source/Image.c ./Source/Convolution.c ./Source/Contour.c   Header/Contour.h
	gcc -o test -Wall main.c  ./Source/Operations.c ./Source/Image.c ./Source/Convolution.c ./Source/Contour.c   ./Header/Contour.h  -I. -lm
run:
	./test
clean:
	rm test
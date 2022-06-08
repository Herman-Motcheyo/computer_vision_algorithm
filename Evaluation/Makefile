CC = gcc
CFLAGS = -Wall -o
LDFLAGS   =  -I -lm

foperation = Operations.o -c Operations.c
fImage =  Image.o -c Image.c 

#Hder = $(wildcard *.h)

traitement_image: main.o  Operations.o
	$(CC) -o traitement_image main.o Operations.o - Operations.h -lm
main.o: main.c
	gcc -o main.o -c main.c

Operations.o: Image.o
	$(CC) -o $(foperation) Image.o $(LDFLAGS) -I Image.h

Image.o:
	$(CC) -o $(fImage) -I Image.h

run:
	./traitement_image
clean:
	rm -rf *.o
	clear
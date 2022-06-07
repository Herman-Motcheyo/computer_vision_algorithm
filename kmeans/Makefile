#######################################


PROG = kmeans

all : $(PROG)

# Variables for file compilation
CC        =  gcc
CFLAGS    =  -g -Wall
CPPFLAGS  =  -DDEBUG
LDFLAGS   =  -g -lm

#pxmtopxm : pxmtopxm.o Util.o

kmeans : kmeans.o Util.o -lm

clean :
	@rm -f *.o

cleanall : clean
	@rm -f $(PROG)


CC=g++
CFLAGS=-std=c++11 -g -Wall 

all: draw encode decode

simplecanvas.o: simplecanvas/simplecanvas.h simplecanvas/simplecanvas.cpp
	$(CC) $(CFLAGS) -c simplecanvas/simplecanvas.cpp

tree.o: tree.cpp tree.h simplecanvas.o
	$(CC) $(CFLAGS) -c tree.cpp

draw: tree.o simplecanvas.o draw.cpp
	$(CC) $(CFLAGS) -o draw draw.cpp tree.o simplecanvas.o

encode: tree.o simplecanvas.o encode.cpp
	$(CC) $(CFLAGS) -o encode encode.cpp tree.o simplecanvas.o

decode: tree.o simplecanvas.o decode.cpp
	$(CC) $(CFLAGS) -o decode decode.cpp tree.o simplecanvas.o

clean:
	rm *.o draw encode decode
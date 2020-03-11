#FLAGS
C++FLAG = -g -std=c++11

MATH_LIBS = -lm

EXEC_DIR=.

.cc.o:
	g++ $(C++FLAG) $(INCLUDES) -c $< -o $@

# Including
INCLUDES= -I.

#-->All libraries (without LEDA)
LIBS_ALL =  -L/usr/lib -L/usr/local/lib 

image.o: image.cc
	g++ $(C++FLAG) image.cc -c -o image.o

h1.o: h1.cc
	g++ $(C++FLAG) h1.cc -c -o h1.o

h1: h1.o image.o
	g++ $(C++FLAG) h1.o image.o -o h1

h2.o: h2.cc
	g++ $(C++FLAG) h2.cc -c -o h2.o

h2: h2.o image.o
	g++ $(C++FLAG) h2.o image.o -o h2

all:
	make h1 h2

clean:
	(rm -f *.o; rm h1)

(:
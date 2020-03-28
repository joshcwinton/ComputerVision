
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

sphere.o: sphere.cc
	g++ $(C++FLAG) sphere.cc -c -o sphere.o

s1.o: s1.cc
	g++ $(C++FLAG) s1.cc -c -o s1.o

s1: s1.o image.o sphere.o
	g++ $(C++FLAG) s1.o image.o sphere.o -o s1

all:
	make s1

clean:
	(rm -f *.o; rm s1)
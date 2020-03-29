
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

matrixUtils.o: matrixUtils.cc
	g++ $(C++FLAG) matrixUtils.cc -c -o matrixUtils.o

s1.o: s1.cc
	g++ $(C++FLAG) s1.cc -c -o s1.o

s1: s1.o image.o sphere.o
	g++ $(C++FLAG) s1.o image.o sphere.o -o s1

s2.o: s2.cc
	g++ $(C++FLAG) s2.cc -c -o s2.o

s2: s2.o image.o sphere.o
	g++ $(C++FLAG) s2.o image.o sphere.o -o s2

s3.o: s3.cc
	g++ $(C++FLAG) s3.cc -c -o s3.o

s3: s3.o 
	g++ $(C++FLAG) s3.o -o s3

all:
	make s1 s2 s3

clean:
	(rm -f *.o; rm s1 s2 s3)
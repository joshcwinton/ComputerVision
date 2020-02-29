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

database.o: database.cc database.h
	g++ $(C++FLAG) database.cc -c -o database.o

p1.o: p1.cc
	g++ $(C++FLAG) p1.cc -c -o p1.o

p1: p1.o image.o
	g++ $(C++FLAG) p1.o image.o -o p1

p2.o: p2.cc
	g++ $(C++FLAG) p2.cc -c -o p2.o

p2: p2.o image.o
	g++ $(C++FLAG) p2.o image.o -o p2

p3.o: p3.cc 
	g++ $(C++FLAG) p3.cc -c -o p3.o

p3: p3.o image.o database.o
	g++ $(C++FLAG) p3.o image.o database.o -o p3

p4.o: p4.cc
	g++ $(C++FLAG) p4.cc -c -o p4.o

p4: p4.o image.o database.o
	g++ $(C++FLAG) p4.o image.o database.o -o p4

all:
	make p1 p2 p3 p4

clean:
	(rm -f *.o; rm p1 p2 p3 p4)

(:


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

houghUtils.o: houghUtils.cc
	g++ $(C++FLAG) houghUtils.cc -c -o houghUtils.o
	
h1.o: h1.cc
	g++ $(C++FLAG) h1.cc -c -o h1.o

h1: h1.o image.o
	g++ $(C++FLAG) h1.o image.o -o h1

h2.o: h2.cc
	g++ $(C++FLAG) h2.cc -c -o h2.o

h2: h2.o image.o
	g++ $(C++FLAG) h2.o image.o -o h2

h3.o: h3.cc
	g++ $(C++FLAG) h3.cc -c -o h3.o

h3: h3.o image.o
	g++ $(C++FLAG) h3.o image.o -o h3

h4.o: h4.cc
	g++ $(C++FLAG) h4.cc -c -o h4.o

h4: h4.o image.o houghUtils.o
	g++ $(C++FLAG) h4.o image.o houghUtils.o -o h4

all:
	make h1 h2 h3 h4

clean:
	(rm -f *.o; rm h1 h2 h3 h4)

runall:
	make run1
	make run2

run1:
	./h1 hough_simple_1.pgm h1Output.1.pgm
	./h2 h1Output.1.pgm 115 h2Output.1.pgm	
	./h3 h2Output.1.pgm h3Output.1.pgm h3Output.1.txt
	./h4 hough_simple_1.pgm h3Output.1.txt 400 h4Output.1.pgm

run2:
	./h1 hough_simple_2.pgm h1Output.2.pgm
	./h2 h1Output.2.pgm 115 h2Output.2.pgm	
	./h3 h2Output.2.pgm h3Output.2.pgm h3Output.2.txt
	./h4 hough_simple_2.pgm h3Output.2.txt 400 h4Output.2.pgm

(:

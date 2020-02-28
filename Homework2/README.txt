PARTS COMPLETED
Part 1: 
  - Program that converts grayscale pgm to binary using a given threshold
  - I used 120 for the threshold

Part 2:
  - Program that displays segmented objects with different grayscale values
  - Algorithm based on the one described at: [https://en.wikipedia.org/wiki/Connected-component_labeling#One_component_at_a_time]

Part 3:
  - Program that generates a database based on a labeled image and then draws lines to indicate orientation

BUGS ENCOUNTERED
- Triggered abort when drawing lines that go off edge of image
- Viewing pgm through mac preview didn't properly display gray levels

INSTRUCTIONS
Part 1:
  - make clean
  - make p1
  - ./p1 {inputimage} {threshold} {outputimage}

Part 2:
  - make clean 
  - make p2
  - ./p2 {inputimage} {outputimage}

Part 3:
  - make clean
  - make p3
  - ./p3 {inputimage} {outputimage}

INPUT/OUTPUT FILES
Part 1:
  Input: objects.pgm
  Output: p1Output.pgm

Part 2:
  Input: p1Output.pgm
  Output: p2Output.pgm

Part 3:
  Input: p2Output.pgm
  Output: p3Output.pgm, p3Database.txt


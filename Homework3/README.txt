PARTS COMPLETED
Part 1: 
  - Program that locates edges in a gray level image and generates an "edge" image where the intensity at each point is proportional to edge magnitude
  - Used Squared Gradient Sobel operator as convolution mask

Part 2:
   - Program that thresholds the image so that only strong edges remain
   - Used code from previous assignment
   - Kind of tricky to get strong edges only without deleting some edges, I used threshold = 65

Part 3:
   
INSTRUCTIONS
Part 1:
  - make clean
  - make h1
  - ./h1 {inputimage} {outputimage}

Part 2:
   - make clean
   - make h2
   - ./h2 {inputimage} {threshold} {outputimage}

INPUT/OUTPUT FILES
Part 1:
  Input: hough_simple_1.pgm
  Output: h1Output.pgm

Part 2:
   Input: h1Output.pgm
   Output: h2Output.pgm
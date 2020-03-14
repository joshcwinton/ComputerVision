Josh Winton
Computer Vision Homework 3

NOTE: After running make clean and make all, you can run "make runall" to 
run all of the programs sequentially on the two simple input images with the same thresholds I used

PARTS COMPLETED
Part 1: 
  - Program that locates edges in a gray level image and generates an "edge" image where the intensity at each point is proportional to edge magnitude
  - Used Squared Gradient Sobel operator as convolution mask

Part 2:
  - Program that thresholds the image so that only strong edges remain
  - Used code from previous assignment
  - Kind of tricky to get strong edges only without deleting some edges, I used THRESHOLD = 65

Part 3:
  - Program that applies Hough transform to produce an image that represents lines in the rho/theta space

Part 4:
  - Converts Hough array to an image
  - Uses Image member functions to detect centers of areas of brightness using a given threshold
  - Uses detected centers as lines in the image from its Hough Transform space 
  - Draws the detected lines on a copy of the original scene image
  - Identifies most straight lines correctly, but angled lines aren't right

INSTRUCTIONS
Part 1:
  - make clean
  - make h1
  - ./h1 {inputimage} {outputimage}

Part 2:
   - make clean
   - make h2
   - ./h2 {inputimage} {threshold} {outputimage}

Part 3: 
  - make clean 
  - make h3 
  - ./h3 {input-binary-edge-image} {output-gray-level-hough-image} {output-hough-voting-array}

Part 4:
  - make clean
  - make h4
  - ./h4 {input-original-gray-level-image} {input-hough-voting-array} {input-hough-threshold-value} {output-gray-level-line-image}

INPUT/OUTPUT FILES
Part 1:
  Input: hough_simple_1.pgm
  Output: h1Output.pgm

Part 2:
  Input: h1Output.pgm
  Output: h2Output.pgm

Part 3:
  Input: h2Output.pgm
  Output: h3Output.pgm, h3Output.txt

Part 4:
  Input: hough_simple_1.pgm, h3Output.txt
  Output: h4Output.pgm
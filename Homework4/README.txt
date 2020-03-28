Josh Winton
Computer Vision Homework 4

PARTS COMPLETED
Part 1: 
  - Locates the sphere in an image and computes its center and radius
  - Used threshold=100
  - Outputs x, y, radius seperated by a space

Part 2: 
  - Computes directions and intensities of light sources
  - Using formula n=(x/√(r^2-x^2-y^2), y/√(r^2-x^2-y^2), 1) to get surface normal at a given point (x, y) centered around the circle center and radius r
  - Using brightest pixel on spere in each image to find surface normal and illumination intensity


INSTRUCTIONS
Part 1:
  - make clean
  - make s1
  - ./s1 sphere0.pgm 100 s1Output.txt

Part 2: 
  - make clean
  - make s2
  - ./s2 s1Output.txt sphere1.pgm sphere2.pgm sphere3.pgm s2Output.txt

INPUT/OUTPUT FILES
Part 1:
  Input: sphere0.pgm
  Output: s1Output.txt

Part 2:
  Input: s1Output.txt sphere1.pgm sphere2.pgm sphere3.pgm
  Output: s2Output.txt

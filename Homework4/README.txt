		      ____________________________

		       COMPUTER VISION HOMEWORK 4

			      Josh Winton
		      ____________________________


Table of Contents
_________________

1 Parts Completed
.. 1.1 Sphere Location (s1)
..... 1.1.1 Input/Output Files
..... 1.1.2 Instructions to Run s1
.. 1.2 Lighting Directions (s2)
..... 1.2.1 Input/Output Files
..... 1.2.2 Instructions to Run s2
.. 1.3 Surface Normals (s3)





1 Parts Completed
=================

1.1 Sphere Location (s1)
~~~~~~~~~~~~~~~~~~~~~~~~

  - The program *s1* locates a sphere in a given gray-level image and
    computes its center and radius
  - I used 100 as my threshold
  - Outputs x, y, and radius to a given text file seperated by a space


1.1.1 Input/Output Files
------------------------

  - Input:
    - sphere0.pgm
  - Output:
    - s1Output.txt


1.1.2 Instructions to Run s1
----------------------------

  ,----
  | $ make clean
  | $ make s1
  | $ ./s1 sphere0.pgm 100 s1Output.txt
  `----


1.2 Lighting Directions (s2)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  - Uses 3 images, each with different lighting conditions and the
    sphere in the same position as in the previous step to compute
    lighting directions and intenstity
  - Used formula $n=[x/(sqrt(r^2-x^2-y^2), y/(sqrt(r^2-x^2-y^2), 1]$ to
    compute surface normals at a given point on the circle (x, y) with
    its origin at the circle center
  - Used brightest pixel on sphere in each image to find illumination
    direction and intensity
  - Can assume brightest pixel on sphere is oriented toward illumination
    because for a Lambertian surface radiance depends only on lighting
    direction and not viewing direction, so the brightest point will be
    oriented toward the light source


1.2.1 Input/Output Files
------------------------

  - Input:
    - s1Output.txt
    - sphere1.pgm
    - sphere2.pgm
    - sphere3.pgm
  - Ouput:
    - s2Output.txt


1.2.2 Instructions to Run s2
----------------------------

  ,----
  | $ make clean
  | $ make s2
  | $ ./s2 s1Output.txt sphere1.pgm sphere2.pgm sphere3.pgm s2Output.txt
  `----


1.3 Surface Normals (s3)
~~~~~~~~~~~~~~~~~~~~~~~~

  - Given 3 images of an object, compute the normals to that object's
    surface
  - 

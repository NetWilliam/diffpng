#diffpng

Compare two .png image files based on Hector Yee's PerceptualDiff algorithm

"Perceptual Metric for Production Testing", 2004/1/1, Journal of Graphics Tools

###hows it work?

The top two images can be compared with 'diffpng img1.png img2.png -o diff.png'.
*![OpenSCAD Monotone example](/master/test/ossphere_mono.png "OpenSCAD Monotone")
*![OpenSCAD Color example](/master/test/ossphere_color2.png "OpenSCAD Color")
The resulting diff.png looks like this: (red=same, black=difference)
*![diffpng result](/master/test/diffpng_example.png "diffpng example")

###license

* Copyright (C) 2006-2011 Yangli Hector Yee (PerceptualDiff)
* Copyright (C) 2011-2014 Steven Myint (PerceptualDiff)
* Copyright (C) 2014 Don Bright

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details in the
file LICENSE

###build & install

    Get Cmake (http://www.cmake.org)
    cmake . && make
    ctest # run regression tests
    make install DESTDIR="/home/me/mydist"

###usage

    diffpng image1.png image2.png [options]
    --verbose : Turns on verbose mode
    --fov deg : Field of view, deg, in degrees. Usually between 10.0 to 85.0.
                This controls how much of the screen the observer is seeing.
                Front row of a theatre has a field of view of around 25
                degrees. Back row has a field of view of around 60 degrees.
    --threshold p : Sets the number of pixels, p, to reject. For example if p
                    is 100, then the test fails if 100 or more pixels are
                    perceptibly different.
    --gamma g : The gamma to use to convert to RGB linear space. Default is 2.2
    --luminance l : The luminance of the display the observer is seeing.
                    Default is 100 candela per meter squared
    --colorfactor : How much of color to use, 0.0 to 1.0, 0.0 = ignore color.
    --scale : Scale images to match each other's dimensions.
    --sum-errors : Print a sum of the luminance and color differences.
    --maxlevels n : Set the maximum number of Laplacian Pyramids to use.
      (less is faster)
    --output foo.png : Save a diff image, black=different, red=same. 

###design philosophy

1. simple
2. portable
3. no dependencies
4. small
5. regression tests

###todo

* make all .hpp header files
* figure out why --luminanceonly works for the openscad tests (color v color2 esp)
* dtermine why more than 2 or 3 levels of pyramid is needed, or not?
* test openscad objects from files.openscad.org/tests that have little tiny pieces that are different.

###credits

For the original PerceptualDiff (PDiff):

* Hector Yee, author of original PerceptualDiff. http://hectorgon.blogspot.com
* Steven Myint, major fork. https://github.com/myint/perceptualdiff 
* PerceptualDiff contributors: Scott Corley, Tobias Sauerwein, Cairo Team, Jim Tilander, Jeff Terrace
* PDiff's Threshold vs Intensity function, Ward Larson Siggraph 1997
* PDiff's Contrast sensitivity function, Barten SPIE 1989
* PDiff's Visual Masking Function, Daly 1993
* PDiff's Adobe(TM) RGB->XYZ matrix from http://www.brucelindbloom.com/
* PDiff's ABGR format, http://partners.adobe.com/asn/developer/PDFS/TN/TIFF6.pdf

For diffpng:

* Lode Vandevenne's lodepng. http://lodev.org/lodepng/

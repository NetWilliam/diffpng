diffpng
=======

Compare two .png image files

##license

Copyright (C) 2006-2011 Yangli Hector Yee (PerceptualDiff)

Copyright (C) 2011-2014 Steven Myint (PerceptualDiff)

Copyright (C) 2014 Don Bright

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details in the
file LICENSE

##build & install

    Get Cmake (http://www.cmake.org)
    cmake . && make
    make install DESTDIR="/home/me/mydist"


##usage

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
    --downsample : How many powers of two to down sample the image.
    --scale : Scale images to match each other's dimensions.
    --sum-errors : Print a sum of the luminance and color differences.
    --output foo.ppm : Saves the difference image to foo.ppm

##design philosophy

1. simple
2. portable
3. no dependencies
4. small
5. regression tests



#diffpng

Compare two .png image files using modified Hector Yee's PerceptualDiff algorithm

Based on Yee's paper "Perceptual Metric for Production Testing", 2004/1/1, Journal of Graphics Tools

###hows it work?

Consider these two images. Are they the same or not?

![example1](/test/matches/circ1.png "OpenSCAD Color")
![example2](/test/matches/circ2.png "OpenSCAD Monotone")

They are very close to being the same, to the human eye, but if you 
carefully examine them they are slightly different. If you loaded two 
copies on the same screen and flipped back and forth quickly, you would 
see the tiny differences.

But how can we compare them using a computer? We need a 'perceptual 
difference' that takes into account the human visual system and how it 
interprets visual images. Hence, Hector Yee's algorithm, and diffpng 
which is based on it.

We can compare these two images using diffpng as follows:

    diffpng img1.png img2.png --output diff.png

The program will print a text message indicating the images look the same

    MATCHES: Images are roughly the same

Now consider two differing images.

![OpenSCAD Color example](/test/differs/ossphere_color2_1.png "OpenSCAD Color")
![OpenSCAD Monotone example](/test/differs/ossphere_color2_2.png "OpenSCAD Monotone")

If we compare them with diffpng, we will get a different result.

    DIFFERS: Images are perceptually different

The program will also produce an image highlighting the differences. 
The resulting diff.png looks like this: (black=same, red=difference)

![diffpng result](/test/basic/diffpng_example.png "diffpng example")

So. Diffpng will allow you to write programs that can detect, roughly,
whether two images "look the same" to the human eye, even if they are
slightly different, while it can also detect images that "look different"
to the human eye.

###build & install

diffpng consists of a single C++ language file, diffpng.cpp, alongside 
Lode Vandevenne's lodepng.cpp/lodepng.h for PNG image loading. 
diffpng.cpp can be used by itself to generate an executable program, or 
it can be used as a header file in another C++ program.

To build as an executable program 'diffpng':

    # Get Cmake (http://www.cmake.org)
    mkdir bin && cd bin && cmake ..
    ctest # run regression tests
    cp ./diffpng /wherever/you/want

To use as a header file in your own program:

Imagine you have a program 'myprogram.cpp'. Put these two lines at the top.

    #define DIFFPNG_HEADERONLY
    #include "diffpng.cpp"

Now call diffpng using the same method used in main() at the bottom of the file.
(Note your program will also need lodepng)

###usage

    diffpng image1.png image2.png --output diff.png

    for other options, run diffpng --help

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

####modifications of Yee's & Myint's perceptual diff

1. Same basic algorithm
2. Modified "Max Laplacian Pyramid Levels" to be settable at runtime
3. Start with 2 max pyramid levels. It can quickly detect a good match.
4. Only if 2 levels detects a mismatch will we increase the levels, 
   default to 5. This means that for very similar images, the program
   runs pretty fast. For 512x512, usually less than 2 seconds.
5. If 2 through 5 all fail, then try Downsampling and blurring the image,
   and also shifting it by a few pixels. Re-run the comparisons.
6. Alter Default colorlevel setting. Try to balance between ignoring
   small differences in background tones, but not accepting images with
   big pixel differences.

This acheives a level of perceptual diff that is extremely roughly 
equivalent of the following ImageMagick comparison:

    convert img1 img2 -alpha Off -compose difference -composite -threshold 10% -morphology Erode Square -format "%[fx:w*h*mean]" info:

It was made to work with the regression test system of the OpenSCAD project.
 
###design philosophy

1. simple
2. portable
3. no dependencies
4. small
5. regression tests
6. no crashes, no freezes

practical effects of philosophy:

1. use very plain C++, in the style of python or Go. 
   avoid exceptions, pointers, stdc++0, 'auto', etc.
2. as few files as possible (one, plus two for lodepng)
3. make default settings so it 'just works' for most ordinary situations
4. use a large amount of regression test images (under test/ dir)
5. the size of the test system is far larger than the program itself.
6. output MATCHES and DIFFERS (not PASS/FAIL). this avoids confusion 
   running ctest (some images should differ, and detecting this is a Ctest 
   PASS not a failure).
7. use standard unix return values. 0 = MATCHES, 1 = DIFFERS

long term goals:

1. no pointers at all
2. less than 1000 lines of code
3. make fail-test run in less than 3 seconds. 
4. unicode filenames under windows(TM)
5. 'just works' paralellism

###what about Imagemagick and phash?

ImageMagick is a huge dependency to require when a program only requires 
simple image comparison. It is also difficult to 'strip out' the ImageMagick 
image compare code from the rest of the ImageMagick code base. 
ImageMagick also has a history of portability problems, crash bugs, 
backwards incompatability between versions, etc etc, which make it 
unsuitable for regression testing in some situations.

phash is also rather large, and a basic use of it produces false 
matches, for example look at diffpng's "differs" tests. There are two 
images that should produce a non-match. 'spher1.png' and 'spher2.png'.

Using pyPhash:

>>> h1 = pHash.imagehash('difffpng/test/differs/spher1.png')
>>> h2 = pHash.imagehash('difffpng/test/differs/spher2.png')
>>> print pHash.hamming_distance( h1, h2), h1, h2
0 4261506436910995169 4261506436910995169

Note the hashes match exactly. That's a problem for regression testing.

###todo

clarify issue with chroma vs luminance. . . do color swatches produce diffs?
can we use colorfactor 0.1 or 0.05? 

should tiny speckled pixels count as 'different'?

clarify the 'default settings' vs what settings user can alter.

windows unicode filenames

###ctest

The built in test suite allows you to modify diffpng's algorithms while
testing what the practical effect will be. 

Test images are stored in two main directories, under 'test', like so.
Consider two files:

    test/differs/file1.png
    test/differs/file2.png

file1.png and file2.png should differ

Now consider these two:

    test/matches/img1.png
    test/matches/img2.png

img1.png and img2.png should match

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
* OpenSCAD regression test images http://github.com/openscad/openscad/tests


/*
RGBAImage.hpp
Copyright (C) 2006-2011 Yangli Hector Yee
Copyright (C) 2011-2014 Steven Myint
(This entire file was rewritten by Jim Tilander)
Copyright (C) 2014 Don Bright

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place, Suite 330, Boston, MA 02111-1307 USA
*/


/*

This source has been heavily modified from both PerceptualDiff and LodePNG Examples

*/

/*
LodePNG Examples

Copyright (c) 2005-2012 Lode Vandevenne

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation would be
    appreciated but is not required.

    2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

    3. This notice may not be removed or altered from any source
    distribution.
*/

#ifndef DIFFPNG_RGBA_IMAGE_H
#define DIFFPNG_RGBA_IMAGE_H

#include "lodepng.h"
#include <stdint.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

/** Class encapsulating an image containing R,G,B,A channels.
 *
 * Internal representation assumes data is in the ABGR format, with the RGB
 * color channels premultiplied by the alpha value. Premultiplied alpha is
 * often also called "associated alpha" - see the tiff 6 specification for some
 * discussion - http://partners.adobe.com/asn/developer/PDFS/TN/TIFF6.pdf
 *
 */
class RGBAImage
{
	RGBAImage(const RGBAImage &);
	RGBAImage &operator=(const RGBAImage &);

public:
	RGBAImage(unsigned int w, unsigned int h, const std::string &name="")
		: Width(w), Height(h), Name(name), Data(w * h)
	{
	}
	unsigned char Get_Red(unsigned int i) const
	{
		return (Data[i] & 0xFF);
	}
	unsigned char Get_Green(unsigned int i) const
	{
		return ((Data[i] >> 8) & 0xFF);
	}
	unsigned char Get_Blue(unsigned int i) const
	{
		return ((Data[i] >> 16) & 0xFF);
	}
	unsigned char Get_Alpha(unsigned int i) const
	{
		return ((Data[i] >> 24) & 0xFF);
	}
	void Set(unsigned char r, unsigned char g, unsigned char b,
			 unsigned char a, unsigned int i)
	{
		Data[i] = r | (g << 8) | (b << 16) | (a << 24);
	}
	unsigned int Get_Width() const
	{
		return Width;
	}
	unsigned int Get_Height() const
	{
		return Height;
	}
	void Set(unsigned int x, unsigned int y, unsigned int d)
	{
		Data[x + y * Width] = d;
	}
	unsigned int Get(unsigned int x, unsigned int y) const
	{
		return Data[x + y * Width];
	}
	unsigned int Get(unsigned int i) const
	{
		return Data[i];
	}
	const std::string &Get_Name() const
	{
		return Name;
	}
	unsigned int *Get_Data()
	{
		return &Data[0];
	}
	const unsigned int *Get_Data() const
	{
		return &Data[0];
	}

	void WriteToFile(const std::string &filename) const
	{
		std::cout << "WriteToFile:" << filename << "\n";

		unsigned width = this->Width, height = this->Height;
		std::vector<unsigned char> image;
		image.resize(width * height * 4);
		for(unsigned y = 0; y < height; y++) {
		for(unsigned x = 0; x < width; x++) {
			unsigned char red, green, blue, alpha;
			red = Get_Red( y*width + x );
			green = Get_Green( y*width + x );
			blue = Get_Blue( y*width + x );
			alpha = Get_Alpha( y*width + x );
			image[4 * width * y + 4 * x + 0] = red;
			image[4 * width * y + 4 * x + 1] = blue;
			image[4 * width * y + 4 * x + 2] = green;
			image[4 * width * y + 4 * x + 3] = alpha;
		}
		}

		//Encode from raw pixels to disk with a single function call
		//The image argument has width * height RGBA pixels or width * height * 4 bytes
		unsigned error = lodepng::encode(filename.c_str(), image, width, height);

		if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
	}

	static std::shared_ptr<RGBAImage> ReadFromFile(const std::string &filename)
	{
		std::cout << "reading from file:" << filename << "\n";
		std::vector<unsigned char> lodepng_image; //the raw pixels
		unsigned width, height;
		unsigned error = lodepng::decode(lodepng_image, width, height, filename.c_str());
		if (error) {
			std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
			return NULL;
		}

		//the pixels are now in the vector "image", 4 bytes per pixel, 
		//ordered RGBARGBA..., use it as texture, draw it, ...
		std::cout << "width " << width << ", height " << height << "\n";

		std::shared_ptr<RGBAImage> rgbaimg( new RGBAImage(width,height,"newimage") );

		for(unsigned y = 0; y < height; y += 1) {
		for(unsigned x = 0; x < width; x += 1) {
			uint32_t red = lodepng_image[4 * y * width + 4 * x + 0]; //red
			uint32_t green = lodepng_image[4 * y * width + 4 * x + 1]; //green
			uint32_t blue = lodepng_image[4 * y * width + 4 * x + 2]; //blue
			uint32_t alpha = lodepng_image[4 * y * width + 4 * x + 3]; //alpha
			rgbaimg->Set( red, green, blue, alpha, y*width+x );
		}
		}
		return rgbaimg;
	}
private:
	const unsigned int Width;
	const unsigned int Height;
	const std::string Name;
	std::vector<unsigned int> Data;
};

#endif

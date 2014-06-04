/*
RGBAImage.cpp
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

#include <stdint.h>

#include "rgbaimage.h"
#include "lodepng.h"
#include <iostream>

#include <string>
#include <cstring>
#include <cassert>

#define LODEPNG_BITMAP std::vector<unsigned char>

struct LodePNGDeleter
{
	void operator()(LODEPNG_BITMAP *image)
	{
		if (image) image->clear();
	}
};


std::shared_ptr<LODEPNG_BITMAP> ToLodePNG(const RGBAImage &image)
{
	std::shared_ptr<LODEPNG_BITMAP> bitmap;
/*	const *data = image.Get_Data();

	std::shared_ptr<LODEPNG_BITMAP> bitmap(
		LodePNG_Allocate(image.Get_Width(), image.Get_Height(), 32,
							 0x000000ff, 0x0000ff00, 0x00ff0000),
		LodePNGDeleter());
	assert(bitmap.get());

	for (y = 0u; y < image.Get_Height();
		 y++, data += image.Get_Width())
	{
		scanline = reinterpret_cast<unsigned int *>(
			LodePNG_GetScanLine(bitmap.get(), image.Get_Height() - y - 1));
		memcpy(scanline, data, sizeof(data[0]) * image.Get_Width());
	}
*/
	return bitmap;
}

//Encode from raw pixels to disk with a single function call
//The image argument has width * height RGBA pixels or width * height * 4 bytes
void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height)
{
	//Encode the image
	unsigned error = lodepng::encode(filename, image, width, height);

	//if there's an error, display it
	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}


void RGBAImage::WriteToFile(const std::string &filename) const
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

	encodeOneStep(filename.c_str(), image, width, height);
/*	const file_type = LodePNG_GetFIFFromFilename(filename.c_str());
	if (FIF_UNKNOWN == file_type)
	{
		throw RGBImageException("Can't save to unknown filetype '" +
								filename + "'");
	}

	bitmap = ToLodePNG(*this);

	LodePNG_SetTransparent(bitmap.get(), false);
	std::unique_ptr<LODEPNG_BITMAP, LodePNGDeleter> converted(
		LodePNG_ConvertTo24Bits(bitmap.get()));

	const bool result =
		!!LodePNG_Save(file_type, converted.get(), filename.c_str());
	if (not result)
	{
		throw RGBImageException("Failed to save to '" + filename + "'");
	}*/
}

std::shared_ptr<RGBAImage> RGBAImage::ReadFromFile(const std::string &filename)
{
	std::cout << "reading from file:" << filename << "\n";
	LODEPNG_BITMAP lodepng_image; //the raw pixels
	unsigned width, height;
	unsigned error = lodepng::decode(lodepng_image, width, height, filename.c_str());
	if (error) {
		std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
		throw RGBImageException("Failed to load the image " + filename);
	}

	//the pixels are now in the vector "image", 4 bytes per pixel, 
	//ordered RGBARGBA..., use it as texture, draw it, ...
	std::cout << "width " << width << ", height " << height << "\n";

	std::shared_ptr<RGBAImage> rgbaimg( new RGBAImage(width,height,"newimage") );

	for(unsigned y = 0; y < height; y += 1) {
		for(unsigned x = 0; x < width; x += 1) {
			//get RGBA components
			uint32_t red = lodepng_image[4 * y * width + 4 * x + 0]; //red
			uint32_t green = lodepng_image[4 * y * width + 4 * x + 1]; //green
			uint32_t blue = lodepng_image[4 * y * width + 4 * x + 2]; //blue
			uint32_t alpha = lodepng_image[4 * y * width + 4 * x + 3]; //alpha

			//make translucency visible by placing checkerboard pattern behind image
			//int checkerColor = 191 + 64 * (((x / 16) % 2) == ((y / 16) % 2));
			//r = (a * r + (255 - a) * checkerColor) / 255;
			//g = (a * g + (255 - a) * checkerColor) / 255;
			//b = (a * b + (255 - a) * checkerColor) / 255;

			//give the color value to the pixel of the screenbuffer
			//uint32_t* bufp;
			//bufp = (uint32_t *)scr->pixels + (y * scr->pitch / 4) / jump + (x / jump);
			//*bufp = 65536 * r + 256 * g + b;
			rgbaimg->Set( red, green, blue, alpha, y*width+x );
		}
	}
	return rgbaimg;
}

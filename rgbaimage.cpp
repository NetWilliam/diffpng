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

std::shared_ptr<RGBAImage> RGBAImage::DownSample(unsigned int w, unsigned int h) const
{
/*	if (w == 0)
	{
		w = Width / 2;
	}

	if (h == 0)
	{
		h = Height / 2;
	}

	if (Width <= 1 or Height <= 1)
	{
		return nullptr;
	}
	if (Width == w and Height == h)
	{
		return nullptr;
	}
	assert(w <= Width);
	assert(h <= Height);

	bitmap = ToLodePNG(*this);
	std::unique_ptr<LODEPNG_BITMAP, LodePNGDeleter> converted(
		LodePNG_Rescale(bitmap.get(), w, h, FILTER_BICUBIC));

	img = ToRGBAImage(converted.get(), Name);

*/
	std::shared_ptr<RGBAImage> img;
	return img;
}

void RGBAImage::WriteToFile(const std::string &filename) const
{
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
	LODEPNG_BITMAP lodepng_image; //the raw pixels
	unsigned width, height;
	unsigned error = lodepng::decode(lodepng_image, width, height, filename.c_str());
	if (error) {
		std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
		throw RGBImageException("Failed to load the image " + filename);
	}

	//the pixels are now in the vector "image", 4 bytes per pixel, 
	//ordered RGBARGBA..., use it as texture, draw it, ...

	std::shared_ptr<RGBAImage> result( new RGBAImage(width,height,"newimage") );

	return result;
}

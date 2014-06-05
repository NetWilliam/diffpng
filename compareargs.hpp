#ifndef DIFFPNG_COMPARE_ARGS_H
#define DIFFPNG_COMPARE_ARGS_H

/*
Compare Args
Copyright (C) 2006-2011 Yangli Hector Yee
Copyright (C) 2011-2014 Steven Myint

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

#include <memory>
#include <string>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <sstream>

#include "rgbaimage.hpp"

static const auto copyright =
	"diffpng version 2014,\n\
based on PerceptualDiff Copyright (C) 2006 Yangli Hector Yee\n\
diffpng and PerceptualDiff comes with ABSOLUTELY NO WARRANTY;\n\
This is free software, and you are welcome\n\
to redistribute it under certain conditions;\n\
See the GPL page for details: http://www.gnu.org/copyleft/gpl.html\n\n";


static const auto usage = "Usage: diffpng image1 image2\n\
\n\
Compares image1 and image2 using a perceptually based image metric.\n\
\n\
Options:\n\
 --verbose	Turns on verbose mode\n\
 --fov deg	Field of view in degrees (0.1 to 89.9)\n\
 --threshold p   # of pixels p below which differences are ignored\n\
 --gamma g	Value to convert rgb into linear space (default 2.2)\n\
 --luminance l   White luminance (default 100.0 cdm^-2)\n\
 --luminanceonly Only consider luminance; ignore chroma (color) in the comparison\n\
 --colorfactor   How much of color to use, 0.0 to 1.0, 0.0 = ignore color.\n\
 --scale		Scale images to match each other's dimensions.\n\
 --sum-errors	Print a sum of the luminance and color differences.\n\
 --output o.ppm  Write difference to the file o.ppm\n\
 --maxlevels n   set the maximum number of Laplacian Pyramid Levels\n\
\n";



template <typename T>
static T lexical_cast(const std::string &input)
{
	std::stringstream ss(input);
	T output;
	if (not (ss >> output))
	{
		throw std::invalid_argument("");
	}
	return output;
}


static bool option_matches(const char *arg, const std::string &option_name)
{
	const auto string_arg = std::string(arg);

	return (string_arg == "--" + option_name) or
		   (string_arg == "-" + option_name);
}


class RGBAImage;

// Args to pass into the comparison function
class CompareArgs
{
public:
	CompareArgs()
	{
		Verbose = false;
		LuminanceOnly = false;
		SumErrors = false;
		FieldOfView = 45.0f;
		Gamma = 2.2f;
		ThresholdPixels = 100;
		Luminance = 100.0f;
		ColorFactor = 1.0f;
		MaxPyramidLevels = 8;
	}
	bool Parse_Args(int argc, char **argv)
	{
		if (argc < 3)
		{
			std::stringstream ss;
			ss << copyright;
			ss << usage;
			ss << "\n"
			   << "OpenMP status";
#ifdef _OPENMP
			ss << "enabled\n";
#else
			ss << "disabled\n";
#endif
			ErrorStr = ss.str();
			return false;
		}
		auto image_count = 0u;
		const char *output_file_name = NULL;
		for (auto i = 1; i < argc; i++)
		{
			try
			{
				if (option_matches(argv[i], "fov"))
				{
					if (++i < argc)
					{
						FieldOfView = lexical_cast<float>(argv[i]);
					}
				}
				else if (option_matches(argv[i], "verbose"))
				{
					Verbose = true;
				}
				else if (option_matches(argv[i], "threshold"))
				{
					if (++i < argc)
					{
						auto temporary = lexical_cast<int>(argv[i]);
						if (temporary < 0)
						{
							throw std::invalid_argument(
								"-threshold must be positive");
						}
						ThresholdPixels = static_cast<unsigned int>(temporary);
					}
				}
				else if (option_matches(argv[i], "gamma"))
				{
					if (++i < argc)
					{
						Gamma = lexical_cast<float>(argv[i]);
					}
				}
				else if (option_matches(argv[i], "maxlevels"))
				{
					if (++i < argc)
					{
						MaxPyramidLevels = lexical_cast<int>(argv[i]);
					}
				}
				else if (option_matches(argv[i], "luminance"))
				{
					if (++i < argc)
					{
						Luminance = lexical_cast<float>(argv[i]);
					}
				}
				else if (option_matches(argv[i], "luminanceonly"))
				{
					LuminanceOnly = true;
				}
				else if (option_matches(argv[i], "sum-errors"))
				{
					SumErrors = true;
				}
				else if (option_matches(argv[i], "colorfactor"))
				{
					if (++i < argc)
					{
						ColorFactor = lexical_cast<float>(argv[i]);
					}
				}
				else if (option_matches(argv[i], "output"))
				{
					if (++i < argc)
					{
						output_file_name = argv[i];
					}
				}
				else if (image_count < 2)
				{
					auto img = RGBAImage::ReadFromFile(argv[i]);
					if (not img)
					{
						ErrorStr = "FAILCannot open ";
						ErrorStr += argv[i];
						ErrorStr += "\n";
						return false;
					}
					else
					{
						++image_count;
						if (image_count == 1)
						{
							ImgA = img;
						}
						else
						{
							ImgB = img;
						}
					}
				}
				else if (option_matches(argv[i], "help"))
				{
					std::cout << usage;
					return false;
				}
				else
				{
					std::cerr << "Warningoption/file \"" << argv[i]
						  << "\" ignored\n";
				}
			}
			catch (const std::invalid_argument &exception)
			{
				std::string reason = "";
				if (not std::string(exception.what()).empty())
				{
					reason = std::string("; ") + exception.what();
				}
				std::cout << "Invalid argument (" << std::string(argv[i]) <<
									 ") for " << argv[i - 1] << reason;
				return false;
			}
		}

		if (not ImgA or not ImgB)
		{
			ErrorStr = "FAILNot enough image files specified\n";
			return false;
		}

		if (output_file_name)
		{
			ImgDiff.reset(new RGBAImage(ImgA->Get_Width(), ImgA->Get_Height(),
										output_file_name));
		}
		return true;
	}

	void Print_Args() const
	{
		std::cout << "Field of view is " << FieldOfView << " degrees\n"
			  << "Threshold pixels is " << ThresholdPixels << " pixels\n"
			  << "The Gamma is " << Gamma << "\n"
			  << "The Display's luminance is " << Luminance
			  << " candela per meter squared\n"
			  << "Max Laplacian Pyramid Levels is " << MaxPyramidLevels << "\n";
	}

	std::shared_ptr<RGBAImage> ImgA;	 // Image A
	std::shared_ptr<RGBAImage> ImgB;	 // Image B
	std::unique_ptr<RGBAImage> ImgDiff;  // Diff image
	bool Verbose;						// Print lots of text or not
	bool LuminanceOnly;  // Only consider luminance; ignore chroma channels in
						 // the
						 // comparison.
	bool SumErrors;  // Print a sum of the luminance and color differences of
					 // each
					 // pixel.
	float FieldOfView;  // Field of view in degrees
	float Gamma;		// The gamma to convert to linear color space
	float Luminance;	// the display's luminance
	unsigned int ThresholdPixels;  // How many pixels different to ignore
	std::string ErrorStr;		  // Error string

	// How much color to use in the metric.
	// 0.0 is the same as LuminanceOnly = true,
	// 1.0 means full strength.
	float ColorFactor;

	unsigned int MaxPyramidLevels;
};


class ParseException : public virtual std::invalid_argument
{
public:

	ParseException(const std::string &message)
		: std::invalid_argument(message)
	{
	}
};

#endif

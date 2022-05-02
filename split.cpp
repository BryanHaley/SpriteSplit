#include <Magick++.h>
#include <string>
#include <iostream>

using namespace std;
using namespace Magick;

bool split(string input, string output, string format, int rows, int cols, int xoff, int yoff, int width, int height, int hpad, int vpad, int startIndex, string mask)
{
	InitializeMagick(NULL);

	// Create Image object but don't read input image file yet
	Image spritesheet;

	try
	{
		// Read input image
		spritesheet.read(input);

		// Automaticall calculate cell width/height from image dimensions and number of rows/cols
		int cell_width  = (int) (spritesheet.columns()/cols);
		int cell_height = (int) (spritesheet.rows()/rows);

		// override cell width/height if user specified
		if (width > 0)  cell_width  = width;
		if (height > 0) cell_height = height;

		// Note: if cell_width or cell_height is too large, the last sprite will get cropped which is ok

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				// Create sprite as a copy of spritesheet
				// Actual pixel data is stored in the heap and shouldn't be duplicated (I think) so this should be fine
				Image sprite (spritesheet);
				sprite.repage();

				// Get the location in the spritesheet of this cell
				int x = xoff + (j*cell_width) + (j*hpad);
				int y = yoff + (i*cell_height) + (i*vpad);

				// Crop sprite out of spritesheet
				sprite.crop(Geometry(cell_width,cell_height,x,y));

				// Mask out color
				if (mask != "")
				{
					sprite.transparent(Color(mask));
				}

				// Generate an index so each sprite has a unique filename
				int index = (i*cols)+j+startIndex;

				// Create filepath for sprite
				string output_filepath = output + "_" + to_string(index) + "." + format;

				// Don't right _index if we're just cropping
				if (rows == 1 && cols == 1)
				{
					output_filepath = output + "." + format;
				}

				// Output only if sprite isn't empty
				if (sprite.columns() > 0 && sprite.rows() > 0)
				{
					sprite.write(output_filepath);
				}
				else
				{
					cout << "Warning: skipping empty " + output_filepath << endl;
				}
			}
		}
	}
	catch (Exception &e)
	{
		cout << "Imagemagick library exception: " << e.what() << endl;
		return false;
	}

	return true;
}
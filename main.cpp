#include "parg.hh"

#include <string>
#include <iostream>

#define VERSION_NUM "0.1.0"

using namespace std;

// Lazy. Avoid making header file for one function.
bool split(string input, string output, string format, int rows, int cols, int xoff, int yoff, int width, int height, int hpad, int vpad);

int main(int argc, char **argv)
{
	OB::Parg pg {argc, argv};

	pg.name("spritesplit").version(VERSION_NUM);
	pg.description("Splits spritesheet images into individual sprite images");
	pg.author("Bryan Haley");

	pg.usage("[-v|-l|-i|-o|-f|-r|-c|-x|-y|-w|-h|-p|-q]");

	pg.set("help,l", "Print the help output"); // using -l because -h is used for cell height
	pg.set("version,v", "Print the program version");

	pg.set("input,i", "", "filepath", "The input spritesheet image");
	pg.set("output,o", "sprite", "filepath", "The output image (no extension)");

	pg.set("format,f", "png", "image file format", "The output image format (must be supported by imagemagick)");

	pg.set("rows,r", "1", "integer", "The number of rows"); // default value of 1 makes this utility useful for cropping
	pg.set("columns,c", "1", "integer", "The number of columns");

	pg.set("xoff,x", "0", "integer", "Starting x offset");
	pg.set("yoff,y", "0", "integer", "Starting y offset");

	pg.set("width,w", "0", "integer", "Override sprite width");
	pg.set("height,h", "0", "integer", "Override sprite height");

	pg.set("hpad,p", "0", "integer", "The number of padding pixels between cells (horizontal)");
	pg.set("vpad,q", "0", "integer", "The number of padding pixels between cells (vertical)");

	pg.info("Examples", {
    pg.name() + " --help",
    pg.name() + " --version",
    pg.name() + " -i test.jpg -r 2 -c 2",
    pg.name() + " -i test.jpg -r 2 -c 2 -x 27 -y 23 -w 570 -h 380",
    pg.name() + " -i test.jpg -x 27 -y 23 -w 570 -h 380"
  	});

	int status = pg.parse();

	// parsing error
	if (status < 0)
	{
		cout << pg.help() << "\n";
		cout << "Error: " << pg.error() << "\n";
		return -1;
	}

	// no arguments given
	if (status > 0 && pg.get_stdin().empty())
	{
		cout << pg.help() << "\n";
		cout << "Error: No arguments supplied" << "\n";
		return -2;
	}

	if (pg.get<bool>("help"))
	{
		// handle -l and --help
		cout << pg.help();
		return 0;
	}

	if (pg.get<bool>("version"))
	{
		// handle -v and --version
		cout << pg.name() << " v" << pg.version() << "\n";
		return 0;
	}

	// Get args from command line
	string input = pg.get<string>("input");
	string output = pg.get<string>("output");
	string format = pg.get<string>("format");
	int rows = pg.get<int>("rows");
	int cols = pg.get<int>("columns");
	int xoff = pg.get<int>("xoff");
	int yoff = pg.get<int>("yoff");
	int width = pg.get<int>("width");
	int height = pg.get<int>("height");
	int hpad = pg.get<int>("hpad");
	int vpad = pg.get<int>("vpad");

	// Error check
	if (input == "")
	{
		cout << pg.help() << "\n";
		cout << "Error: invalid or no input filepath supplied" << "\n";
		return -3;
	}

	if (output == "")
	{
		cout << pg.help() << "\n";
		cout << "Error: invalid or no output filepath supplied" << "\n";
		return -4;
	}

	if (format == "")
	{
		cout << pg.help() << "\n";
		cout << "Error: invalid or no format argument supplied" << "\n";
		return -5;
	}

	if (rows < 1)
	{
		cout << pg.help() << "\n";
		cout << "Error: invalid or no rows argument supplied" << "\n";
		return -6;
	}

	if (cols < 1)
	{
		cout << pg.help() << "\n";
		cout << "Error: invalid or no cols argument supplied" << "\n";
		return -7;
	}

	// Split up image
	bool success = split(input, output, format, rows, cols, xoff, yoff, width, height, hpad, vpad);

	if (!success)
	{
		cout << "Error occurred during image processing." << "\n";
		return -8;
	}
}
# SpriteSplit

Quick utility to split an image (i.e. a spritesheet) into several smaller images (i.e. sprites), or crop a single sprite out of a spritesheet.

## Usage
```
  spritesplit [-v|-l|-i|-o|-f|-r|-c|-x|-y|-w|-h|-p|-q|-m|-s]

Flags:
  -l, --help
    Print the help output
  -v, --version
    Print the program version

Options:
  -i, --input=<filepath>
    The input spritesheet image
  -o, --output=<filepath>
    The output image (no extension)
  -f, --format=<image file format>
    The output image format (must be supported by imagemagick)
  -r, --rows=<integer>
    The number of rows
  -c, --columns=<integer>
    The number of columns
  -x, --xoff=<integer>
    Starting x offset
  -y, --yoff=<integer>
    Starting y offset
  -w, --width=<integer>
    Override sprite width
  -h, --height=<integer>
    Override sprite height
  -p, --hpad=<integer>
    The number of padding pixels between cells (horizontal)
  -q, --vpad=<integer>
    The number of padding pixels between cells (vertical)
  -m, --mask=<hex>
    Color to mask out as transparent. Accepts SVG color codes (e.g. hex codes or color names like red)
  -s, --startindex=<integer>
    Starting index used for naming

Examples:
  spritesplit --help
  spritesplit --version
  spritesplit -i test.jpg -r 2 -c 2
  spritesplit -i test.jpg -r 2 -c 2 -x 27 -y 23 -w 570 -h 380
  spritesplit -i test.jpg -x 27 -y 23 -w 570 -h 380
  spritesplit -i test.jpg -m "#FEF9F3"
```

## Building

Install the imagemagick++ library. 

On Mac:
```
brew install imagemagick
```

On Ubuntu:
```
sudo apt-get install libgraphicsmagick1-dev
```

Then just run ```make```.
```
make
```

## Installing

On Mac with ```brew``` installed:
```
make install
```

On Ubuntu or Mac without ```brew```:
```
sudo make install
```
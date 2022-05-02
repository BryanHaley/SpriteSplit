# SpriteSplit

Quick utility to split an image (i.e. a spritesheet) into several smaller images (i.e. sprites).

## Usage
```
  spritesplit [-v|-h|-i|-o|-f|-r|-c|-x|-y|-j|-k|-p|-q]

Flags:
  -h, --help
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
  -j, --width=<integer>
    Override sprite width
  -k, --height=<integer>
    Override sprite height
  -p, --hpad=<integer>
    The number of padding pixels between cells (horizontal)
  -q, --vpad=<integer>
    The number of padding pixels between cells (vertical)

Examples:
  spritesplit --help
  spritesplit --version
  spritesplit -i test.jpg -r 2 -c 2
  spritesplit -i test.jpg -r 2 -c 2 -x 27 -y 23 --width=570 --height=380
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
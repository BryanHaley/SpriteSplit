# Simple makefile for SpriteSplit

CXX := g++
RM_FILE := rm -f
MV_FILE := mv

CXX_FLAGS := $(shell Magick++-config --cxxflags --cppflags) -O2 -std=c++11
LD_FLAGS  := $(shell Magick++-config --ldflags --libs)

SRCS := main.cpp split.cpp
EXE  := spritesplit

UNAME := $(shell uname)
ARCH  := $(shell uname -m)

INSTALL_DIR := /usr/local/bin
BREW_PREFIX := $(shell brew --prefix)

# if macOS and brew is installed
ifeq ($(UNAME),Darwin)
	ifneq ($(BREW_PREFIX),)
		INSTALL_DIR := $(BREW_PREFIX)/bin
	else
		INSTALL_DIR := /usr/bin
	endif
endif

all:
	$(CXX) $(CXX_FLAGS) $(SRCS) -o $(EXE) $(LD_FLAGS)
clean:
	-$(RM_FILE) $(EXE)

install:
	$(MV_FILE) $(EXE) $(INSTALL_DIR)/

.PHONY: all clean install
FILES=src/Framebuffer/main.cpp
OUT=src/Framebuffer/fbclient

all: $(FILES)
	g++ -Wall -o $(OUT) $(FILES) -lm -std=c++11 -O3

.PHONY: all

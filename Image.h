#ifndef __IMAGE_SAVER__
#define __IMAGE_SAVER__

//includes
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

//data structures
struct Colour {
	unsigned char r,g,b,a;
};

class TGAImage {

public:
	TGAImage();
	TGAImage(int width, int height);
	void setAllPixels(Colour *pixels);
	void setPixel(Colour inputcolor, int xposition, int yposition);
	void WriteImage(string filename);

	void setWidth(int width);
	void setHeight(int height);

	int getWidth();
	int getHeight();

private:

	Colour *m_pixels;

	int m_height;
	int m_width;

	int convert2dto1d(int x, int y);

};


#endif

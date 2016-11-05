#include "Image.h"

TGAImage::TGAImage() {

}

TGAImage::TGAImage(int width, int height) {
	m_width = width;
	m_height = height;
	m_pixels = new Colour[m_width*m_height];
}

void TGAImage::setAllPixels(Colour *pixels) {
	m_pixels = pixels;
}

void TGAImage::setPixel(Colour inputcolor, int x, int y) {
	m_pixels[convert2dto1d(x,y)] = inputcolor;
}

int TGAImage::convert2dto1d(int x, int y) {
    return ((m_width * x) + y);
}

void TGAImage::WriteImage(string filename) {

	//Error checking
	if (m_width <= 0 || m_height <= 0)
	{
		cout << "Image size is not set properly" << endl;
		return;
	}

	ofstream o(filename.c_str(), ios::out | ios::binary);

	//Write the header                        /*Should look here ?
	o.put(0);
   	o.put(0);
   	o.put(2);                         /* uncompressed RGB */
   	o.put(0); 		o.put(0);
   	o.put(0); 	o.put(0);
   	o.put(0);
   	o.put(0); 	o.put(0);           /* X origin */
   	o.put(0); 	o.put(0);           /* y origin */
   	o.put((m_width & 0x00FF));
   	o.put((m_width & 0xFF00) / 256);
   	o.put((m_height & 0x00FF));
   	o.put((m_height & 0xFF00) / 256);
   	o.put(32);                        /* 24 bit bitmap */
   	o.put(0);

	//Write the pixel data
	for (int i=0;i<m_height*m_width;i++) {
		o.put(m_pixels[i].b);
		o.put(m_pixels[i].g);
		o.put(m_pixels[i].r);
		o.put(m_pixels[i].a);
	}

	//close the file
	o.close();

}

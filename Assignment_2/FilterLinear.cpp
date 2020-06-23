#include "Image.h"
#include "FilterLinear.h"
#include <iostream>
using namespace imaging;


FilterLinear::FilterLinear(){
	this->a = 1;
	this->c = 0;
}

FilterLinear::FilterLinear(Color a, Color c) {
	this->a = a;
	this->c = c;
}

FilterLinear::~FilterLinear() {
	std::cout << "Destruction of Filter linear object" << std::endl;
}

FilterLinear::FilterLinear(const FilterLinear &src) {
	this->a = src.a;
	this->c = src.c;
}

Image FilterLinear::operator << (const Image &image) {
	Image img(image);
	for (unsigned int i = 0; i < img.getWidth(); i++) {
		for (unsigned int j = 0; j < img.getHeight(); j++) {
			Color clr = img.getElement(i, j);
			clr = a * clr + c;
			//----all results must be on interval [0,1]---
			if (clr.r > 1.0)
				clr.r = 1.0;
			if (clr.g > 1.0)
				clr.g = 1.0;
			if (clr.b > 1.0)
				clr.b = 1.0;
			if (clr.r < 0.0)
				clr.r = 0.0;
			if (clr.g < 0.0)
				clr.g = 0.0;
			if (clr.b < 0.0)
				clr.b = 0.0;
			img.setElement(i,j,clr);
		}
	}
	return img;
}
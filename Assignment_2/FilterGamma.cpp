#include "Image.h"
#include "FilterGamma.h"
#include <iostream>
#include <math.h>

using namespace imaging;

FilterGamma::FilterGamma(){
	this->gamma = 1.0;
}

FilterGamma::FilterGamma(float g) {
	this->gamma = g;
}

FilterGamma::~FilterGamma() {
	std::cout << "Destruction of Filter Gamma object" << std::endl;
}

FilterGamma::FilterGamma(const FilterGamma &src) {
	this->gamma = src.gamma;
}

Image FilterGamma::operator << (const Image &image) { 
	Image img(image); //einai const opote dn ginetai na kanw allages sthn image gia auto kaloume ton copy constructor
	for (unsigned int i = 0; i < img.getWidth(); i++) {
		for (unsigned int j = 0; j < img.getHeight(); j++) {
			Color clr = img.getElement(i,j);
			clr.r = pow(clr.r, gamma);
			clr.g = pow(clr.g, gamma);
			clr.b = pow(clr.b, gamma);
			img.setElement(i, j, clr);
		}
	}
	return img;
}
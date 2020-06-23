#pragma once
#ifndef _FILTERGAMMA
#define _FILTERGAMMA
#include "Image.h"
#include "Filter.h"

using namespace imaging;

	class FilterGamma:public Filter
	{

	private:
		float gamma;
	public:
		Image operator << (const Image &image);
		FilterGamma();
		FilterGamma(float g);
		~FilterGamma();
		FilterGamma(const FilterGamma &src);
	};

#endif
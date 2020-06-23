#pragma once
#ifndef _FILTERLINEAR
#define _FILTERLINEAR
#include "Image.h"
#include "Filter.h"

using namespace imaging;

	class FilterLinear:public Filter
	{

	private:
		Color a;
		Color c;

	public:
		Image operator << (const Image &image);
		FilterLinear();
		FilterLinear(Color a, Color c);
		~FilterLinear();
		FilterLinear(const FilterLinear &src);
		
	};

#endif
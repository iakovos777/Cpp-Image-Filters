//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2014
//
//
//-------------------------------------------------------------

#ifndef _FILTER
#define _FILTER
#include "Image.h"

using namespace imaging;

	class Filter
	{

	public:
		virtual Image operator << (const Image &image) = 0;
		Filter () {}
		virtual ~Filter() {}
		Filter(const Filter &src) {
		}
	};


#endif
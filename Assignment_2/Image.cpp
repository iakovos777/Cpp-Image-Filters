#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Image.h"
#include "ppm/ppm.h"
#include "Array.h"
#include "Vec3.h"

using namespace std;

/*! The imaging namespace contains every class or function associated with the image storage, compression and manipulation.
 */
namespace imaging
{

	//------------------------------------ class Image ------------------------------------------------

		/*! It is the class that represents a generic data container for an image.
		 *
		 * It holds the actual buffer of the pixel values and provides methods for accessing them,
		 * either as individual pixels or as a memory block. The Image class alone does not provide
		 * any functionality for loading and storing an image, as it is the result or input to such a procedure.
		 *
		 * The internal buffer of an image object stores the actual bytes (data) of the color image as
		 * a contiguous sequence of Color structures. Hence, the size of the buffer variable holding these data is
		 * width X height X sizeof(Color) bytes.
		 *
		 * All values stored in the Color data type components are assumed to be floating point values and for typical (normalized)
		 * intensity ranges, each color component is within the range [0.0, 1.0].
		 */








		 // constructors and destructor

		 /*! Default constructor.
		  *
		  * By default, the dimensions of the image should be zero and the buffer must be set to nullptr.
		  */
	Image::Image() :Array() {
	}

	/*! Constructor with width and height specification.
	 *
	 * \param width is the desired width of the new image.
	 * \param height is the desired height of the new image.
	 */
	Image::Image(unsigned int width, unsigned int height) :Array(width, height) {
	}

	/*! Constructor with data initialization.
	 *
	 * \param width is the desired width of the new image.
	 * \param height is the desired height of the new image.
	 * \param data_ptr is the source of the data to copy to the internal image buffer.
	 *
	 * \see setData
	 */
	Image::Image(unsigned int width, unsigned int height, const Color * data_ptr) :Array(width, height, data_ptr) {
	}

	/*! Copy constructor.
	 *
	 * \param src is the source image to replicate in this object.
	 */
	Image::Image(const Image &src) :Array(src) {
	}

	/*! The Image destructor.
	 */
	 // I SEE IT
	Image::~Image(){
		if (!buffer.empty())
			vector<Color>().swap(buffer);
		std::cout << "Destruction of Image object" << std::endl;
	}

	/*! Copy assignment operator.
	 *
	 * \param right is the source image.
	 */
	Image & Image::operator = (const Image & right) {
		if (this != &right) {
			Array::operator =(right);
		}
		return *this;
	}

	/*!
	 * Loads the image data from the specified file, if the extension of the filename matches the format string.
	 *
	 * Only the "ppm" extension is supported for now. The extension comparison should be case-insensitive. If the
	 * Image object is initialized, its contents are wiped out before initializing it to the width, height and data
	 * read from the file.
	 *
	 * \param filename is the string of the file to read the image data from.
	 * \param format specifies the file format according to which the image data should be decoded from the file.
	 * Only the "ppm" format is a valid format string for now.
	 *
	 * \return true if the loading completes successfully, false otherwise.
	 */
	bool Image::load(const std::string & filename, const std::string & format) {
		const char * ppm = format.c_str();
		int pos = filename.find(".");
		std::string imExtension = filename.substr(pos + 1, 3);
		const char * extension = imExtension.c_str();
		if (_stricmp(ppm, extension) != 0) {
			std::cout << "Wrong format of image" << std::endl;
			return false;
		}
		if (!buffer.empty())
			vector<Color>().swap(buffer);
		int wid = this->width;
		int hei = this->height;
		int* w = &wid;
		int* h = &hei;
		const char * file = filename.c_str();
		float *data = ReadPPM(file, w, h);
		if (data == nullptr) {
			return false;
		}
		this->width = *w;
		this->height = *h;
		buffer.reserve(width*height);
		unsigned int i = 0;
		unsigned int k = 0;
		while (i < width*height && k < 3 * width*height) {
			Color c(data[k], data[k + 1], data[k + 2]);
			buffer.push_back(c);
			i++;
			k = k + 3;
		}
		delete[] data;
		return true;
	}

	/*!
	* Stores the image data to the specified file, if the extension of the filename matches the format string.
	*
	* Only the "ppm" extension is supported for now. The extension comparison should be case-insensitive. If the
	* Image object is not initialized, the method should return immediately with a false return value.
	*
	* \param filename is the string of the file to write the image data to.
	* \param format specifies the file format according to which the image data should be encoded to the file.
	* Only the "ppm" format is a valid format string for now.
	*
	* \return true if the save operation completes successfully, false otherwise.
	*/
	bool Image::save(const std::string & filename, const std::string & format) {
		const char * ppm = format.c_str();
		int pos = filename.find(".");
		std::string imExtension = filename.substr(pos + 1, 3);
		const char * extension = imExtension.c_str();
		if (_stricmp(ppm, extension) != 0) {
			std::cout << "Wrong format of image" << std::endl;
			return false;
		}
		if (buffer.empty()) {
			std::cout << "Image buffer is not initialized" << std::endl;
			return false;
		}
		int w = this->width;
		int h = this->height;
		const char * file = filename.c_str();
		float *data = new float[3 * width*height];
		unsigned int i = 0;
		unsigned int k = 0;
		//Color ones(1, 1, 1);
		while (i < width*height && k < 3 * width*height) {
			Color c = buffer[i];
			data[k] = c.r;
			data[k + 1] = c.g;
			data[k + 2] = c.b;
			i++;
			k = k + 3;
		}
		if (!WritePPM(data, w, h, file)) {
			return false;
		}
		return true;
	}



}


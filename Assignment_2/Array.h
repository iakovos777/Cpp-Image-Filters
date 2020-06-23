#include <vector>
#include <iostream>
#ifndef _ARRAY_
#define _ARRAY_


#include <string>

using namespace std;

namespace math
{
	template <typename T>
	class Array
	{

	protected:
		vector<T> buffer;                              //! Holds the image data.

		unsigned int width, height;	 				 //! The width of the image (in pixels)
													//! The height of the image (in pixels)

	public:
	
		const unsigned int getWidth() const { return width; }

		
		const unsigned int getHeight() const { return height; }

		
		T * getRawDataPtr() {
			return &buffer.front(); //or &(buffer[0])
		}

		
		T getElement(unsigned int x, unsigned int y) const {
			if (x < width && width>0 && x >= 0) {
				if (y < height && height>0 && y >= 0) {
					if (!buffer.empty()) {
						unsigned int point = y * width + x;
						return buffer[point];
					}
					else
						std::cout << "Image buffer is not initialized" << std::endl;
				}
				else
					std::cout << "Wrong vertical index" << std::endl;

			}
			else
				std::cout << "Wrong horizontal index" << std::endl;
		}

		
		void setElement(unsigned int x, unsigned int y, T & value) {
			if (x < width && width>0 && x >= 0) {
				if (y < height && height>0 && y >= 0) {
					if (buffer.empty()) 
						buffer.reserve(width*height);
					
					unsigned int point = y * width + x;
					T c(value.r, value.g, value.b);
					buffer[point]=c;
				}
				else
					std::cout << "Wrong vertical index" << std::endl;
			}
			else
				std::cout << "Wrong horizontal index" << std::endl;
		}

		
		void setData(const T * & data_ptr) {
			if (buffer.empty()) {
				std::cout << "Buffer is not allocated" << std::endl;
				return;
			}
			if (this->width == 0) {
				std::cout << "Width is 0 " << std::endl;
				return;
			}
			if (this->height == 0) {
				std::cout << "Height is 0" << std::endl;
				return;
			}
			for (unsigned int i = 0; i < width*height; i++) {
				buffer.push_back(data_ptr[i]);
			}
		}



		T & operator () (unsigned int x, unsigned int y) {                      // return a reference to the element at position (column x, row y) 
			if (x < width && width>0 && x >= 0) {
				if (y < height && height>0 && y >= 0) {
					if (!buffer.empty()) {
						unsigned int point = y * width + x;
						return buffer[point];
					}
					else
						std::cout << "Image buffer is not initialized" << std::endl;
				}
				else
					std::cout << "Wrong vertical index" << std::endl;

			}
			else
				std::cout << "Wrong horizontal index" << std::endl;


		}													 // of the array (zeor-based)

		const T & operator () (unsigned int x, unsigned int y) const {         // return a reference to the element at position (column x, row y) 
			if (x < width && width>0 && x >= 0) {
				if (y < height && height>0 && y >= 0) {
					if (!buffer.empty()) {
						unsigned int point = y * width + x;
						return buffer[point];
					}
					else
						std::cout << "Image buffer is not initialized" << std::endl;
				}
				else
					std::cout << "Wrong vertical index" << std::endl;

			}
			else
				std::cout << "Wrong horizontal index" << std::endl;

		}													 // of the array (zeor-based)

		
		Array() {
			this->width = 0;
			this->height = 0;
			buffer.reserve(0);
		}

		
		Array(unsigned int width, unsigned int height) {
			bool c1 = false, c2 = false;
			if (width >= 0) {
				this->width = width;
				c1 = true;
			}
			else
				std::cout << "Invalid width" << std::endl;
			if (height >= 0) {
				this->height = height;
				c2 = true;
			}
			else
				std::cout << "Invalid height" << std::endl;
			if (c1 && c2) {
				buffer.reserve(width*height);
			}
		}

		/*! Constructor with data initialization.
		 *
		 * \param width is the desired width of the new image.
		 * \param height is the desired height of the new image.
		 * \param data_ptr is the source of the data to copy to the internal image buffer.
		 *
		 * \see setData
		 */
		Array(unsigned int width, unsigned int height, const T * data_ptr) {
			this->width = width;
			this->height = height;
			unsigned int size = width * height;
			buffer.reserve(size);
			this->setData(data_ptr);
		}

		/*! Copy constructor.
		 *
		 * \param src is the source image to replicate in this object.
		 */
		Array(const Array<T> &src){
			this->width = src.width;
			this->height = src.height;
			unsigned int size = this->width * this->height;
			buffer.reserve(size);
			for (unsigned int i = 0; i < width*height; i++) {
				buffer.push_back(src.buffer[i]);
			}
			//DEBUG
			//std::cout << "\t- Image Copy-Constructor" << std::endl;
		}

		/*! The Image destructor.
		 */
		virtual ~Array(){
			if (!buffer.empty())
				vector<T>().swap(buffer);
			std::cout << "Destruction of Array object" << std::endl;
		}

		/*! Copy assignment operator.
		 *
		 * \param right is the source image.
		 */
		Array & operator = (const Array<T> & right) {
			if (this != &right) {
				if (!buffer.empty())
					vector<T>().swap(buffer);
				this->width = right.width;
				this->height = right.height;
				unsigned int size = this->width * this->height;
				buffer.reserve(size);
				for (unsigned int i = 0; i < width*height; i++) {
					buffer.push_back(right.buffer[i]);
				}
			}
			return *this;
		}

		
		

	};

} //namespace math

#endif

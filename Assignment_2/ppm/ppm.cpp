#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <string.h>

#include "ppm.h"

using namespace std;
//using namespace imaging;

namespace imaging {
	float * ReadPPM(const char * filename, int * w, int * h) {
		fstream file(filename, ios::in | ios::binary);
		string format;
		int wid;
		int hei;
		int maxValueOfPixel;
		if (file.fail()) {
			printf("File not found!\n");
			return nullptr;
		}
		if (!file.is_open()) {
			printf("Could not open image!\n");
			return nullptr;
		}
		//ELEGXOI THS EPIKEFALIDAS
				
		file >> format;
		const char * p6 = format.c_str();
		if (_stricmp(p6, "P6") != 0) {
			cout << "Your image is not P6" << endl;
			return nullptr;
		}
		
		file >> wid;
		if (wid<=0) {
			cout << "Missing the width of image" << endl;
			return nullptr;
		}
		
		file >> hei;
		if (hei <= 0) {
			cout << "Missing the height of image" << endl;
			return nullptr;
		}
		
		file >> maxValueOfPixel;
		if (maxValueOfPixel == 0 ) {
			cout << "Missing the maximum value of pixels of image" << endl;
			return nullptr;
		}
		else if (maxValueOfPixel > 255 || maxValueOfPixel < 0) {
			cout << "Wrong with maximum value of pixels of image" << endl;
			return nullptr;
		}
		
		//--------------------------------------------------
		*w = wid;
		*h = hei;
		int bufferSize = wid * hei * 3;
		unsigned char *buffer = new unsigned char[bufferSize];
		int position = file.tellg();
		file.seekg(position+1, ios::beg); 
		file.read((char *)buffer, bufferSize);
		file.close();
		float *pixels = new float[bufferSize];
		int *test = new int[10];
		for (int i = 0; i < bufferSize; i++) {
			pixels[i] = (float)((float)(buffer[i])/255);
		}
		return &pixels[0];	
	}


	
	bool WritePPM(const float * data, int w, int h, const char * filename) {
		fstream file(filename, ios::out | ios::binary);

		if (!file.is_open()) {
			printf("Could not open image!\n");
			return false;
		}
		int buffer = 3 * w *h;
		string header= "P6\n"+std::to_string(w)+"\n"+std::to_string(h)+"\n255\n";
		file.write(header.c_str(), header.size());
		for (int i = 0; i < buffer; i++) {
			float val = (float)(data[i]*255);
			unsigned char rgb = val ;
			file.write((char *)&rgb, sizeof(unsigned char));
		}
		// Make sure everything passed into the file
		file.flush();
		//file.clear();
		file.close();
		delete[] data;
		return true;
	}
}
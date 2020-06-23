#include <iostream>
#include "Array.h"
#include "Image.h"
#include "Filter.h"
#include <stdio.h>
#include <string>
#include <vector>
#include "FilterLinear.h"
#include "FilterGamma.h"

using namespace std;
using namespace imaging;

int main(int argc, char *argv[]) {
	string filename;
	if (argc == 1) {
		cout << "YOU DIDN'T INSERT AN INPUT "<< endl ;
		system("PAUSE");
		return -1;
	}
	
	if ((_stricmp(argv[3], "linear") != 0) && (_stricmp(argv[3], "gamma")!=0)) {
		system("PAUSE");
		return -1;
	}

	vector<string> filters;
	for (unsigned int k = 0; k < argc; k++) {
		if (_stricmp(argv[k], "-f") == 0) {
			if ((_stricmp(argv[k+1], "linear") == 0) || (_stricmp(argv[k+1], "gamma") == 0)) {
				filters.push_back(argv[k+1]);
			}
			else {
				cout << "WRONG NAME OF FILTER OR NONE FILTER"<<endl;
				system("PAUSE");
				return -1;
			}
		}
	}

	filename = argv[argc - 1];
	//erase if there is whitespace in the start of filename
	if (filename[0] == ' ') filename.erase(0, 1);
	//create name of negative file
	int pos = filename.find(".");
	if (pos < 0) {
		cout << "Something went wrong in name of file" << endl;
		system("PAUSE");
		return -1;
	}

	string filter_filename;
	int flag = -1;
	for (int i = 0; i < filename.length() - 1; i++) {   //check filename with path?
		if (filename[i]=='\\' || filename[i] == '//') {
			flag=i;
		}
	}

	if (flag>=0) {  
		string strF = filename.substr(0, flag + 1);
		string strL = filename.substr(flag + 1, filename.length());
		filter_filename = strF + "filtered_" + strL;
	}
	else {
		filter_filename = "filtered_" + filename;
	}
	
	string format = "ppm";
	Image image;
	Color a, c; 
	float gM; 
	Filter *filter;
	if (!image.load(filename, format)) {
		cout << "Something went wrong while loading the image" << endl;
		system("PAUSE");
		return -1;
	}
	else {
		cout << "Image dimensions are: " << image.getWidth() << " X " << image.getHeight() << endl;
		//cout << image.buffer.size() << endl; //Debug
		unsigned int i = 1;
		const char * fn = filename.c_str();
		while (_stricmp(argv[i],fn)!= 0) {
			if (_stricmp(argv[i], "-f") == 0) {
				i++;
				if (_stricmp(argv[i], "linear") == 0) {
					cout << "FILTER LINEAR:" << endl;
					a = Color(atof(argv[i + 1]), atof(argv[i + 2]), atof(argv[i + 3]));
					c = Color(atof(argv[i + 4]), atof(argv[i + 5]), atof(argv[i + 6]));
					filter = new FilterLinear(a, c);
					image = *filter << image;							
					delete filter;
					i += 7;
				}
				if (_stricmp(argv[i], "gamma") == 0) {
					cout << "FILTER GAMMA:" << endl;
					gM = atof(argv[i + 1]);
					if (gM <= 2.0 && gM >= 0.5) {
						filter = new FilterGamma(gM);
						image = *filter << image;
						delete filter;
						i += 2;
					}
					else {
						cout << "FALSE VALUE FOR VARIABLE GAMMA" << endl;
						return -1;
					}
				}
			}
			else 
				i++;
			
		}
	}



	if (!image.save(filter_filename, format)) {
		cout << "Something went wrong while saving the negative image " << endl;
		system("PAUSE");
		return -1;
	}
	else {
		cout << "Creation of filtered image: " << filter_filename << " in the same path" << endl;
	}
	
	system("PAUSE");
	return 0;
}
//
//  Image.h
//  Papaya
//
//  Created by Guo Chen on 6/17/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Image_h
#define Image_h

#include <string>
#include <vector>
#include <fstream>
#include "Pixel.h"

using std::string;
using std::vector;
using std::ofstream;

enum ImageFormat {
	bmp, jpg, png, ppm
};

class Image {
public:
	virtual void exportTo(const vector<vector<Pixel>> &pixels, const string &fileName) = 0;
};

class PortablePixmap: public Image {
public:
	void exportTo(const vector<vector<Pixel>> &pixels, const string &fileName) {
		ofstream ofs;
		ofs.open(fileName, std::ios::out);
		ofs << "P6 " << std::to_string(pixels[0].size())
			<< " " << std::to_string(pixels.size())
			<< " 255\n";
		ofs.close();
		ofs.open(fileName, std::ios::app|std::ios::binary);
		for (const auto &row: pixels) {
			for (const auto &col: row) {
				ofs << col.r()
					<< col.g()
					<< col.b();
			}
		}
		ofs.close();
	}
};

#endif /* Image_h */

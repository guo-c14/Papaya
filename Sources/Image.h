//
//  Image.h
//  Papaya
//
//  Created by Guo Chen on 6/17/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Image_h
#define Image_h

#include <cstdint>
#include <string>
#include <vector>
#include <fstream>
#include "Vector.h"

using std::string;
using std::vector;
using std::ofstream;

enum ImageFormat {
	bmp, jpg, png, ppm
};

class Image {
public:
	virtual void exportTo(const vector<vector<Vector>> &v, const string &fileName) = 0;
};

class PortablePixmap: public Image {
public:
	void exportTo(const vector<vector<Vector>> &v, const string &fileName) {
		ofstream ofs;
		ofs.open(fileName, std::ios::out);
		ofs << "P6 " << std::to_string(v[0].size())
			<< " " << std::to_string(v.size())
			<< " 255\n";
		ofs.close();
		ofs.open(fileName, std::ios::app|std::ios::binary);
		for (const auto &row: v) {
			for (const auto &col: row) {
				ofs << static_cast<uint8_t>(col.r * 255)
					<< static_cast<uint8_t>(col.g * 255)
					<< static_cast<uint8_t>(col.b * 255);
			}
		}
		ofs.close();
	}
};

#endif /* Image_h */

//
//  ImageIO.cpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include <fstream>
#include "ImageIO.hpp"

using std::ofstream;

void BMPIO::importImage(vector<vector<Color>> &pixels, const string &fileName) {

}

void BMPIO::exportImage(const vector<vector<Color>> &pixels, const string &fileName) {

}

void JPGIO::importImage(vector<vector<Color>> &pixels, const string &fileName) {
	
}

void JPGIO::exportImage(const vector<vector<Color>> &pixels, const string &fileName) {
	
}

void PNGIO::importImage(vector<vector<Color>> &pixels, const string &fileName) {
	
}

void PNGIO::exportImage(const vector<vector<Color>> &pixels, const string &fileName) {
	
}

void PPMIO::importImage(vector<vector<Color>> &pixels, const string &fileName) {
	
}

void PPMIO::exportImage(const vector<vector<Color>> &pixels, const string &fileName) {
	ofstream ofs;
	ofs.open(fileName, std::ios::out);
	ofs << "P6 "
		<< std::to_string(pixels[0].size())
		<< " "
		<< std::to_string(pixels.size())
		<< " 255\n";
	ofs.close();
	ofs.open(fileName, std::ios::app|std::ios::binary);
	for (const auto &row: pixels) {
		for (const auto &col: row) {
			ofs << col.r << col.g << col.b;
		}
	}
	ofs.close();
}

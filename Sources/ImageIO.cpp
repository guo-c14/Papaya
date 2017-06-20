//
//  ImageIO.cpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include <fstream>
#include "ImageIO.hpp"

using std::ifstream;
using std::ofstream;

void BMPIO::importImage(vector<vector<Vec3D>> &pixels, const string &fileName) {

}

void BMPIO::exportImage(const vector<vector<Color>> &pixels, const string &fileName) {

}

void JPGIO::importImage(vector<vector<Vec3D>> &pixels, const string &fileName) {
	
}

void JPGIO::exportImage(const vector<vector<Color>> &pixels, const string &fileName) {
	
}

void PNGIO::importImage(vector<vector<Vec3D>> &pixels, const string &fileName) {
	
}

void PNGIO::exportImage(const vector<vector<Color>> &pixels, const string &fileName) {
	
}

void PPMIO::importImage(vector<vector<Vec3D>> &pixels, const string &fileName) {
	string temp;
	int size = static_cast<int>(3 * pixels.size() * pixels[0].size());
	char *buffer = new char[size];
	ifstream ifs;
	ifs.open(fileName, std::ios::in|std::ios::binary);
	ifs >> temp >> temp >> temp >> temp;
	ifs.get();
	ifs.read(buffer, size);
	ifs.close();
	int width = static_cast<int>(pixels[0].size());
	int height = static_cast<int>(pixels.size());
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			pixels[i][j].x = static_cast<uint8_t>(buffer[3 * width * i + 3 * j]);
			pixels[i][j].y = static_cast<uint8_t>(buffer[3 * width * i + 3 * j + 1]);
			pixels[i][j].z = static_cast<uint8_t>(buffer[3 * width * i + 3 * j + 2]);
			pixels[i][j] /= 255;
		}
	}
	delete [] buffer;
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
	ofs.open(fileName, std::ios::app | std::ios::binary);
	for (const auto &row: pixels) {
		for (const auto &col: row) {
			ofs << col.r << col.g << col.b;
		}
	}
	ofs.close();
}

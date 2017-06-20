//
//  Texture.cpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include "Texture.hpp"

ConstantTexture::ConstantTexture(const Vec3D &color): color(color) {}

Vec3D ConstantTexture::value(double u, double v, const Vec3D &p) const {
	return color;
}

CheckerTexture::CheckerTexture(Texture *odd, Texture *even, double scale):
	odd(odd), even(even), scale(scale) {}

Vec3D CheckerTexture::value(double u, double v, const Vec3D &p) const {
	double sines = sin(scale * p.x) * sin(scale * p.y) * sin(scale * p.z);
	if (sines < 0) {
		return odd->value(u, v, p);
	} else {
		return even->value(u, v, p);
	}
}

ImageTexture::ImageTexture(const string &fileName, ImageFormat format,
						   int width, int height): width(width), height(height) {
	ImageIO *imageIO;
	switch (format) {
		case bmp:
			imageIO = new BMPIO;
			break;
		case jpg:
			imageIO = new JPGIO;
			break;
		case png:
			imageIO = new PNGIO;
			break;
		case ppm:
			imageIO = new PPMIO;
			break;
	}
	pixels = vector<vector<Vec3D>>(height);
	for (int i = 0; i < height; i++) {
		pixels[i] = vector<Vec3D>(width);
	}
	imageIO->importImage(pixels, fileName);
}

Vec3D ImageTexture::value(double u, double v, const Vec3D &p) const {
	int row = (1 - v) * height - 0.001;
	if (row < 0) {
		row = 0;
	}
	if (row > height - 1) {
		row = height - 1;
	}
	int col = (1 - u) * width;
	if (col < 0) {
		col = 0;
	}
	if (col > width - 1) {
		col = width - 1;
	}
	return pixels[row][col];
}

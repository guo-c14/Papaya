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

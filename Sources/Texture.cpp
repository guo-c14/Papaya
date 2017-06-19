//
//  Texture.cpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include <cmath>
#include "Texture.hpp"

ConstantTexture::ConstantTexture(Vec3D color): color(color) {}

Vec3D ConstantTexture::value(double u, double v, const Vec3D &p) const {
	return color;
}

CheckerTexture::CheckerTexture(Texture *odd, Texture *even, double ratio):
	odd(odd), even(even), ratio(ratio) {}

Vec3D CheckerTexture::value(double u, double v, const Vec3D &p) const {
	double sines = sin(ratio * p.x) * sin(ratio * p.y) * sin(ratio * p.z);
	if (sines < 0) {
		return odd->value(u, v, p);
	} else {
		return even->value(u, v, p);
	}
}

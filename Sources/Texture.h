//
//  Texture.h
//  Papaya
//
//  Created by Guo Chen on 6/18/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Texture_h
#define Texture_h

#include <cmath>
#include "Vector.h"
#include "Pixel.h"

class Texture {
public:
	virtual Vector value(double u, double v, const Vector &p) const = 0;
};

class ConstantTexture: public Texture {
public:
	Vector color;
	ConstantTexture() {}
	ConstantTexture(Vector c): color(c) {}
	Vector value(double u, double v, const Vector &p) const {
		return color;
	}
};

class CheckerTexture: public Texture {
public:
	Texture *odd;
	Texture *even;
	CheckerTexture() {}
	CheckerTexture(Texture *odd, Texture *even): odd(odd), even(even) {}
	Vector value(double u, double v, const Vector &p) const {
		double sines = sin(2 * p.x) * sin(2 * p.y) * sin(2 * p.z);
		if (sines < 0) {
			return odd->value(u, v, p);
		} else {
			return even->value(u, v, p);
		}
	}
};

#endif /* Texture_h */

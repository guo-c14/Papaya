//
//  Pixel.h
//  Papaya
//
//  Created by Guo Chen on 6/17/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Pixel_h
#define Pixel_h

#include <cstdint>
#include "Vector.h"

class Pixel: public Vector {
public:
	Pixel(double d = 0): Vector(d) {}
	Pixel(double r, double g, double b): Vector(r, g, b) {}
	Pixel(const Vector &v): Vector(v.x, v.y, v.z) {}
	uint8_t r() const {
		return x * 255.99;
		// return (x / norm() / 2 + 0.5) * 255.99;
	}
	uint8_t g() const {
		return y * 255.99;
		// return (y / norm() / 2 + 0.5) * 255.99;
	}
	uint8_t b() const {
		return z * 255.99;
		// return (z / norm() / 2 + 0.5) * 255.99;
	}
};

#endif /* Pixel_h */

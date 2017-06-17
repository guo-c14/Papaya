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
	Pixel(const Pixel &pixel): Vector(pixel.x, pixel.y, pixel.z) {}
	uint8_t r() const {
		return x / norm() * 255;
	}
	uint8_t g() const {
		return y / norm() * 255;
	}
	uint8_t b() const {
		return z / norm() * 255;
	}
};

#endif /* Pixel_h */

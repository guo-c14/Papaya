//
//  Color.cpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include "Color.hpp"

Color::Color(uint8_t u): elem{u, u, u} {}

Color::Color(uint8_t r, uint8_t g, uint8_t b): elem{r, g, b} {}

Color::Color(const Vec3D &v) {
	*this = v;
}

Color &Color::operator=(const Vec3D &v) {
	Vec3D normalized = v;
	if (normalized.x > 1) {
		normalized.x = 1;
	}
	if (normalized.y > 1) {
		normalized.y = 1;
	}
	if (normalized.z > 1) {
		normalized.z = 1;
	}
	normalized = Vec3D {
		pow(normalized.x, 0.5),
		pow(normalized.y, 0.5),
		pow(normalized.z, 0.5)
	};
	normalized *= 255.999;
	r = static_cast<uint8_t>(normalized.x);
	g = static_cast<uint8_t>(normalized.y);
	b = static_cast<uint8_t>(normalized.z);
	return *this;
}

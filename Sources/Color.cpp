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
	Vec3D normalized;
	if (v.x < 0 || v.y < 0 || v.z < 0) {
		normalized = (normalize(v) + 1) * 127.99;
	} else if (v.x > 1 || v.y > 1 || v.z > 1) {
		normalized = normalize(v);
	} else {
		normalized = v;
	}
	r = static_cast<uint8_t>(normalized.x);
	g = static_cast<uint8_t>(normalized.y);
	b = static_cast<uint8_t>(normalized.z);
}

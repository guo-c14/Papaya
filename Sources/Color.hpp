//
//  Color.hpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Color_hpp
#define Color_hpp

#include <cstdint>
#include "Vec3D.hpp"

class Color {
protected:
	uint8_t elem[3];
public:
	uint8_t &r = elem[0];
	uint8_t &g = elem[1];
	uint8_t &b = elem[2];
	Color(uint8_t u = 0);
	Color(uint8_t r, uint8_t g, uint8_t b);
	Color(const Vec3D &v);
	Color &operator=(const Vec3D &v);
	uint8_t operator[](int index) const;
	uint8_t &operator[](int index);
};

inline Color &Color::operator=(const Vec3D &v) {
	Vec3D normalized;
	if (v.x < 0 || v.y < 0 || v.z < 0) {
		normalized = (normalize(v) + 1) * 127.999;
	} else if (v.x > 1 || v.y > 1 || v.z > 1) {
		normalized = normalize(v) * 255.999;
	} else {
		normalized = v * 255.999;
	}
	r = static_cast<uint8_t>(normalized.x);
	g = static_cast<uint8_t>(normalized.y);
	b = static_cast<uint8_t>(normalized.z);
	return *this;
}

inline uint8_t Color::operator[](int index) const {
	return elem[index];
}

inline uint8_t &Color::operator[](int index) {
	return elem[index];
}

#endif /* Color_hpp */

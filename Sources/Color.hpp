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

inline uint8_t Color::operator[](int index) const {
	return elem[index];
}

inline uint8_t &Color::operator[](int index) {
	return elem[index];
}

#endif /* Color_hpp */

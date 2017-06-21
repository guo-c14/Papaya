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

//
//  Vec3D.cpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include "Vec3D.hpp"

Vec3D::Vec3D(double d): elem{d, d, d} {}

Vec3D::Vec3D(double x, double y, double z): elem{x, y, z} {}

Vec3D::Vec3D(const Vec3D &v): elem{v.x, v.y, v.z} {}

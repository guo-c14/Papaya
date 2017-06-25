//
//  Ray.cpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include "Ray.hpp"

Ray::Ray() {}

Ray::Ray(const Vec3D &origin, const Vec3D &direction, double time):
	origin(origin), direction(normalize(direction)), time(time) {}

Ray::Ray(const Ray &ray): origin(ray.origin), direction(ray.direction),
	time(ray.time) {}

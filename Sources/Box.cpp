//
//  Box.cpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include "Box.hpp"

Box::Box() {}

Box::Box(const Vec3D &min, const Vec3D &max): min(min), max(max) {}

bool Box::hit(const Ray &ray, double tmin, double tmax) const {
	for (int i = 0; i < 3; i++) {
		double invD = 1.0 / ray.direction[i];
		double t0, t1;
		if (invD < 0) {
			t0 = (max[i] - ray.origin[i]) * invD;
			t1 = (min[i] - ray.origin[i]) * invD;
		} else {
			t0 = (min[i] - ray.origin[i]) * invD;
			t1 = (max[i] - ray.origin[i]) * invD;
		}
		tmin = t0 > tmin ? t0 : tmin;
		tmax = t1 < tmax ? t1 : tmax;
		if (tmax <= tmin) {
			return false;
		}
	}
	return true;
}

//
//  Utility.hpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Utility_hpp
#define Utility_hpp

#include <limits>
#include "Vec3D.hpp"

const double PI = 3.141592653589793;
const double PI_180 = 0.017453292519943295;
const double PI_360 = 0.008726646259971648;
const double MAX_DOUBLE = std::numeric_limits<double>::max();
const double MIN_DOUBLE = std::numeric_limits<double>::min();

double drand();

inline double ddmin(double a, double b) {
	return a < b ? a : b;
}

inline double ddmax(double a, double b) {
	return a > b ? a : b;
}

inline bool refract(const Vec3D &v, const Vec3D &n, double ni_over_nt, Vec3D &refracted) {
	Vec3D uv = normalize(v);
	double dt = dot(uv, n);
	double discriminant = 1 - ni_over_nt * ni_over_nt * (1 - dt * dt);
	if (discriminant > 0) {
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}
	else
		return false;
}

inline Vec3D reflect(const Vec3D &v, const Vec3D &n) {
	return v - 2 * dot(v, n) * n;
}

inline Vec3D random_in_unit_sphere() {
	Vec3D p;
	do {
		p = Vec3D(drand(), drand(), drand()) * 2 - 1;
	} while (p.norm2() >= 1);
	return p;
}

inline Vec3D random_in_unit_disk() {
	Vec3D p;
	do {
		p = Vec3D(drand(), drand(), 0) * 2 - Vec3D(1, 1, 0);
	} while (p.norm2() >= 1);
	return p;
}

#endif /* Utility_hpp */

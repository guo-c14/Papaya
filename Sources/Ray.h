//
//  Ray.h
//  Papaya
//
//  Created by Guo Chen on 6/17/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Ray_h
#define Ray_h

#include <cmath>
#include <ostream>
#include "Vector.h"

using std::ostream;

class Ray {
public:
	Vector origin, direction;
	Vector &a=origin, &A=origin;
	Vector &b=direction, &B=direction;
	Ray() {}
	Ray(const Vector &a, const Vector &b): origin(a), direction(normalize(b)) {}
	Ray(const Ray &ray): origin(ray.origin), direction(ray.direction) {}
	Ray &operator=(const Ray &r) {
		a = r.a;
		b = r.b;
		return *this;
	}
	Vector pointAt(double t) const {
		return a + b * t;
	}
};

inline ostream &operator<<(ostream &os, const Ray &ray) {
	os << "Ray{\n\torigin = " << ray.origin << ",\n\tdirection = " << ray.direction << "\n}";
	return os;
}

inline float schlick(double cosine, double ref_idx) {
	double r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}

inline bool refract(const Vector &v, const Vector &n, float ni_over_nt, Vector &refracted) {
	Vector uv = normalize(v);
	float dt = dot(uv, n);
	float discriminant = 1.0 - ni_over_nt*ni_over_nt * (1 - dt * dt);
	if (discriminant > 0) {
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}
	else
		return false;
}


inline Vector reflect(const Vector &v, const Vector &n) {
	return v - 2 * dot(v, n) * n;
}

inline Vector random_in_unit_sphere() {
	Vector p;
	do {
		p = 2.0 * Vector(drand48(), drand48(), drand48()) - 1.0;
	} while (p.norm2() >= 1.0);
	return p;
}

inline Vector random_in_unit_disk() {
	Vector p;
	do {
		p = 2.0 * Vector(drand48(), drand48(), 0) - Vector(1, 1, 0);
	} while (dot(p, p) >= 1.0);
	return p;
}

#endif /* Ray_h */

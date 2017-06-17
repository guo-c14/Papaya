//
//  Ray.h
//  Papaya
//
//  Created by Guo Chen on 6/17/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Ray_h
#define Ray_h

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

#endif /* Ray_h */

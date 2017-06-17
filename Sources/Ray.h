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
	Ray(const Vector &a, const Vector &b): origin(a), direction(normalize(b)) {}
	Ray(const Ray &ray): origin(ray.origin), direction(ray.direction) {}
	Vector pointAt(double t) const {
		return a + b * t;
	}
};

inline ostream &operator<<(ostream &os, const Ray &ray) {
	os << "Ray{\n\torigin = " << ray.origin << ",\n\tdirection = " << ray.direction << "\n}";
	return os;
}

#endif /* Ray_h */

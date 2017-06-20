//
//  Ray.hpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Ray_hpp
#define Ray_hpp

#include "Vec3D.hpp"

class Ray {
public:
	Vec3D origin;
	Vec3D direction;
	double time;
	Ray();
	Ray(const Vec3D &origin, const Vec3D &direction, double time = 0);
	Ray(const Ray &ray);
	Ray &operator=(const Ray &ray);
	Vec3D pointAt(double t) const;
};

inline Vec3D Ray::pointAt(double t) const {
	return origin + direction * t;
}

#endif /* Ray_hpp */

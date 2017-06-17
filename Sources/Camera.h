//
//  Camera.h
//  Papaya
//
//  Created by Guo Chen on 6/17/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Camera_h
#define Camera_h

#include <cmath>
#include "Vector.h"
#include "Ray.h"

const double PI = 3.14159265358979323846264338327950288;

class Camera {
public:
	Vector origin;
	Vector low_left_corner;
	Vector horizontal;
	Vector vertical;
	Vector u, v, w;
	Camera(Vector lookfrom, Vector lookat, Vector vup, double vfov, double aspect) {
		double theta = vfov * PI / 180;
		double half_height = tan(theta / 2);
		double half_width = aspect * half_height;
		origin = lookfrom;
		w = normalize(lookfrom - lookat);
		u = normalize(cross(vup, w));
		v = cross(w, u);
		low_left_corner = origin - half_width * u - half_height * v - w;
		horizontal = 2 * half_width * u;
		vertical = 2 * half_height * v;
	}
	Ray getRay(double s, double t) {
		return Ray(origin, low_left_corner + s * horizontal + t * vertical - origin);
	}
};

#endif /* Camera_h */

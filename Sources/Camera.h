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
	double lens_radius;
	Camera(Vector lookfrom, Vector lookat, Vector vup, double vfov, double aspect, double aperture, double focus_dist) {
		lens_radius = aperture / 2;
		double theta = vfov * PI / 180;
		double half_height = tan(theta / 2);
		double half_width = aspect * half_height;
		origin = lookfrom;
		w = normalize(lookfrom - lookat);
		u = normalize(cross(vup, w));
		v = cross(w, u);
		low_left_corner = origin  - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
		horizontal = 2 * half_width * focus_dist * u;
		vertical = 2 * half_height * focus_dist * v;
	}
	Ray getRay(double s, double t) {
		Vector rd = lens_radius * random_in_unit_disk();
		Vector offset = u * rd.x + v * rd.y;
		return Ray(origin + offset, low_left_corner + s * horizontal + t * vertical - origin - offset);
	}
};

#endif /* Camera_h */

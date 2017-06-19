//
//  Camera.cpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include "Camera.hpp"

Camera::Camera(Vec3D lookfrom, Vec3D lookat, Vec3D vup, double vfov, double aspect,
	double aperture, double focus_dist, double time0, double time1):
	time0(time0), time1(time1) {
	lens_radius = aperture * 0.5;
	double theta = vfov * PI_360;
	double half_height = tan(theta);
	double half_width = aspect * half_height;
	origin = lookfrom;
	w = normalize(lookfrom - lookat);
	u = normalize(cross(vup, w));
	v = cross(w, u);
	low_left_corner = origin  - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
	horizontal = 2 * half_width * focus_dist * u;
	vertical = 2 * half_height * focus_dist * v;
}

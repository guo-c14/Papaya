//
//  Camera.cpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include "Camera.hpp"

Camera::Camera(Vec3D lookfrom, Vec3D lookat, Vec3D vup, double vfov,
	double aspect, double aperture, double focus_dist,
	double exposure_start_time, double exposure_stop_time):
	c(lookfrom), lens_radius(aperture * 0.5),
	exposure_start_time(exposure_start_time),
	exposure_stop_time(exposure_stop_time) {
	double theta = vfov * PI_360;
	double unit_half_height = tan(theta);
	double unit_half_width = aspect * unit_half_height;
	Vec3D w = normalize(lookfrom - lookat);
	u = normalize(cross(vup, w));
	v = cross(w, u);
	o = c - (u * unit_half_width + v * unit_half_height + w) * focus_dist;
	x = 2 * unit_half_width * focus_dist * u;
	y = 2 * unit_half_height * focus_dist * v;
}

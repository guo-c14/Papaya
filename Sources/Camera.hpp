//
//  Camera.hpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "Ray.hpp"
#include "Utility.hpp"

class Camera {
protected:
	Vec3D c, u, v;
	Vec3D o, x, y;
	double lens_radius;
	double exposure_start_time, exposure_stop_time;
public:
	Camera() = default;
	Camera(Vec3D lookfrom, Vec3D lookat, Vec3D vup, double vfov, double aspect,
		double aperture, double focus_dist, double exposure_start_time,
		double exposure_stop_time);
	Ray emitRay(double s, double t) const;
};

inline Ray Camera::emitRay(double s, double t) const {
	Vec3D random_radius = random_in_unit_disk() * lens_radius;
	Vec3D offset = u * random_radius.x + v * random_radius.y;
	double time = exposure_start_time + drand() * (exposure_stop_time - exposure_start_time);
	return Ray(c + offset, o + x * s + y * t - c - offset, time);
}

#endif /* Camera_hpp */

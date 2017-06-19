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

class Camera {
public:
	Vec3D origin;
	Vec3D low_left_corner;
	Vec3D horizontal;
	Vec3D vertical;
	Vec3D u, v, w;
	double lens_radius;
	double time0, time1;
	Camera(Vec3D lookfrom, Vec3D lookat, Vec3D vup, double vfov, double aspect,
		   double aperture, double focus_dist, double time0, double time1);
	Ray emitRay(double s, double t) const;
};

inline Ray Camera::emitRay(double s, double t) const {
	Vec3D rd = lens_radius * random_in_unit_disk();
	Vec3D offset = u * rd.x + v * rd.y;
	double time = time0 + drand() * (time1 - time0);
	return Ray(origin + offset, low_left_corner + s * horizontal + t * vertical - origin - offset, time);
}

#endif /* Camera_hpp */

//
//  Camera.h
//  Papaya
//
//  Created by Guo Chen on 6/17/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Camera_h
#define Camera_h

#include "Vector.h"
#include "Ray.h"

class Camera {
public:
	Vector origin;
	Vector low_left_corner;
	Vector horizontal;
	Vector vertical;
	Camera() {
		low_left_corner = {-2.0, -1.0, -1.0};
		horizontal = {4.0, 0.0, 0.0};
		vertical = {0.0, 2.0, 0.0};
		origin = {0.0, 0.0, 0.0};
	}
	Ray getRay(double u, double v) {
		return {origin, low_left_corner + u * horizontal + v * vertical - origin};
	}
};

#endif /* Camera_h */

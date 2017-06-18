//
//  AABB.h
//  Papaya
//
//  Created by Guo Chen on 6/18/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef AABB_h
#define AABB_h

#include "Vector.h"
#include "Ray.h"

inline double ddmin(double a, double b) { return a < b ? a : b; }
inline double ddmax(double a, double b) { return a > b ? a : b; }

class AABB {
public:
	Vector min, max;
	AABB() {}
	AABB(const Vector &a, const Vector &b): min(a), max(b) { }
	bool hit(const Ray &r, double tmin, double tmax) const {
		for (int i = 0; i < 3; i++) {
			double invD = 1.0 / r.direction[i];
			double t0, t1;
			if (invD < 0.0) {
				t0 = (max[i] - r.origin[i]) * invD;
				t1 = (min[i] - r.origin[i]) * invD;
			} else {
				t0 = (min[i] - r.origin[i]) * invD;
				t1 = (max[i] - r.origin[i]) * invD;
			}
			tmin = t0 > tmin ? t0 : tmin;
			tmax = t1 < tmax ? t1 : tmax;
			if (tmax <= tmin) {
				return false;
			}
		}
		return true;
	}
};

inline AABB surroundBox(AABB box0, AABB box1) {
	Vector min {
		ddmin(box0.min.x, box1.min.x),
		ddmin(box0.min.y, box1.min.y),
		ddmin(box0.min.z, box1.min.z)
	};
	Vector max {
		ddmax(box0.max.x, box1.max.x),
		ddmax(box0.max.y, box1.max.y),
		ddmax(box0.max.z, box1.max.z)
	};
	return {min, max};
}

#endif /* AABB_h */

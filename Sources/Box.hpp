//
//  Box.hpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Box_hpp
#define Box_hpp

#include "Ray.hpp"

class Box {
public:
	Vec3D min, max;
	Box();
	Box(const Vec3D &min, const Vec3D &max);
	bool hit(const Ray &ray, double tmin, double tmax) const;
};

inline Box surroundBox(Box box0, Box box1) {
	Vec3D min {
		ddmin(box0.min.x, box1.min.x),
		ddmin(box0.min.y, box1.min.y),
		ddmin(box0.min.z, box1.min.z)
	};
	Vec3D max {
		ddmax(box0.max.x, box1.max.x),
		ddmax(box0.max.y, box1.max.y),
		ddmax(box0.max.z, box1.max.z)
	};
	return {min, max};
}

#endif /* Box_hpp */

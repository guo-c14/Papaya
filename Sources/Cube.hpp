//
//  Cube.hpp
//  Papaya
//
//  Created by Guo Chen on 6/21/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Cube_hpp
#define Cube_hpp

#include "Rectangle.hpp"

class Cube: public Object {
protected:
	Vec3D min, max;
	ObjectList *list;
public:
	Cube(const Vec3D &min, const Vec3D &max, Material *material);
	virtual bool hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const;
	virtual bool boundingBox(double t0, double t1, BBox &box) const;
};

#endif /* Cube_hpp */

//
//  Circle.hpp
//  Papaya
//
//  Created by Guo Chen on 6/22/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Circle_hpp
#define Circle_hpp

#include "Object.hpp"
#include "Material.hpp"

class Circle: public Object {
protected:
	Vec3D center;
	double radius;
	Material *material;
public:
	Vec3D normal = {0, 1, 0};
	Circle(const Vec3D &center, const Vec3D &normal, double radius, Material *material);
	virtual bool hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const;
	virtual bool boundingBox(double t0, double t1, BBox &box) const;
};

#endif /* Circle_hpp */

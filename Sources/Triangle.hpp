//
//  Triangle.hpp
//  Papaya
//
//  Created by Guo Chen on 6/22/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Triangle_hpp
#define Triangle_hpp

#include "Object.hpp"

class Triangle: public Object {
protected:
	Vec3D vertex[3];
	Vec3D &v0 = vertex[0];
	Vec3D &v1 = vertex[1];
	Vec3D &v2 = vertex[2];
	Material *material;
public:
	Vec3D normal; // default normal = (v0, v1) cross (v0, v2)
	Triangle(const Vec3D &v0, const Vec3D &v1, const Vec3D &v2, Material *material);
	virtual bool hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const;
	virtual bool boundingBox(double t0, double t1, BBox &box) const;
};

#endif /* Triangle_hpp */

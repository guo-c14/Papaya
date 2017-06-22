//
//  Sphere.hpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Sphere_hpp
#define Sphere_hpp

#include "Object.hpp"
#include "Material.hpp"

class Sphere: public Object {
protected:
	Vec3D center;
	double radius;
	Material *material;
public:
	Sphere(const Vec3D &center, double radius, Material *material);
	virtual bool hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const;
	virtual bool boundingBox(double t0, double t1, BBox &box) const;
};

class MovingSphere: public Object {
protected:
	Vec3D center0, center1;
	double time0, time1;
	double radius;
	Material *material;
public:
	MovingSphere(const Vec3D &center0, const Vec3D &center1, double t0, double t1,
		double radius, Material *material);
	Vec3D center(double time) const;
	virtual bool hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const;
	virtual bool boundingBox(double t0, double t1, BBox &box) const;
};

inline Vec3D MovingSphere::center(double time) const {
	return center0 + (time - time0) / (time1 - time0) * (center1 - center0);
}

#endif /* Sphere_hpp */

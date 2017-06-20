//
//  Rectangle.hpp
//  Papaya
//
//  Created by Guo Chen on 6/20/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Rectangle_hpp
#define Rectangle_hpp

#include "Object.hpp"
#include "Material.hpp"

class RectangleXY: public Object {
protected:
	double x0, x1, y0, y1, k;
	Material *material;
public:
	RectangleXY(double x0, double x1, double y0, double y1, double k, Material *material);
	virtual bool hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const;
	virtual bool boundingBox(double t0, double t1, BBox &box) const;
};

class RectangleYZ: public Object {
protected:
	double y0, y1, z0, z1, k;
	Material *material;
public:
	RectangleYZ(double y0, double y1, double z0, double z1, double k, Material *material);
	virtual bool hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const;
	virtual bool boundingBox(double t0, double t1, BBox &box) const;
};

class RectangleXZ: public Object {
protected:
	double x0, x1, z0, z1, k;
	Material *material;
public:
	RectangleXZ(double x0, double x1, double z0, double z1, double k, Material *material);
	virtual bool hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const;
	virtual bool boundingBox(double t0, double t1, BBox &box) const;
};

#endif /* Rectangle_hpp */

//
//  Object.hpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include <vector>
#include "BBox.hpp"
#include "HitRecord.hpp"

using std::vector;

class Object {
public:
	virtual bool hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const = 0;
	virtual bool boundingBox(double t0, double t1, BBox &box) const = 0;
};

class ObjectList: Object {
public:
	vector<Object *> list;
public:
	ObjectList(const vector<Object *> &list);
	virtual bool hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const;
	virtual bool boundingBox(double t0, double t1, BBox &box) const;
};

class FlipNormal: public Object {
protected:
	Object *object;
public:
	FlipNormal(Object *object);
	virtual bool hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const;
	virtual bool boundingBox(double t0, double t1, BBox &box) const;
};

class Translate: public Object {
protected:
	Object *object;
	Vec3D offset;
public:
	Translate(Object *object, const Vec3D &offset);
	virtual bool hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const;
	virtual bool boundingBox(double t0, double t1, BBox &box) const;
};

class RotateY: public Object {
protected:
	Object *object;
	double sin_theta, cos_theta;
	bool exist_bbox;
	BBox bbox;
public:
	RotateY(Object *object, double theta);
	virtual bool hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const;
	virtual bool boundingBox(double t0, double t1, BBox &box) const;
};

#endif /* Object_hpp */

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
#include "Box.hpp"
#include "HitRecord.hpp"

using std::vector;

class Object {
public:
	virtual bool hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const = 0;
	virtual bool boundingBox(double t0, double t1, Box &box) const = 0;
};

class ObjectList: Object {
public:
	vector<Object *> list;
public:
	ObjectList(const vector<Object *> &list);
	virtual bool hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const;
	virtual bool boundingBox(double t0, double t1, Box &box) const;
};

#endif /* Object_hpp */

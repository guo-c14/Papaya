//
//  Object.h
//  Papaya
//
//  Created by Guo Chen on 6/17/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Object_h
#define Object_h

#include <vector>
#include "Vector.h"
#include "Ray.h"

using std::vector;

class Material;

struct HitRecord {
	double t;
	Vector p;
	Vector normal;
	Material *material;
};

class Object {
public:
	virtual bool hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const = 0;
};

class ObjectList: public Object {
public:
	vector<Object *> list;
	ObjectList() {}
	ObjectList(vector<Object *> list): list(list) {}
	bool hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const {
		HitRecord tempRecord;
		bool hitAnything = false;
		double closest = tMax;
		for (int i = 0; i < list.size(); i++) {
			if (list[i]->hit(ray, tMin, closest, tempRecord)) {
				hitAnything = true;
				closest = tempRecord.t;
				record = tempRecord;
			}
		}
		return hitAnything;
	}
};

#endif /* Object_h */

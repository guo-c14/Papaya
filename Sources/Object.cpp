//
//  Object.cpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include "Object.hpp"

ObjectList::ObjectList(const vector<Object *> &list): list(list) {}

bool ObjectList::hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const {
	HitRecord tempRecord;
	bool hitAnything = false;
	double closest = tmax;
	for (int i = 0; i < list.size(); i++) {
		if (list[i] != nullptr && list[i]->hit(ray, tmax, closest, tempRecord)) {
			hitAnything = true;
			closest = tempRecord.t;
			record = tempRecord;
		}
	}
	return hitAnything;
}

bool ObjectList::boundingBox(double t0, double t1, Box &box) const {
	if (list.size() < 1) {
		return false;
	}
	Box temp;
	if (list[0] != nullptr && list[0]->boundingBox(t0, t1, temp)) {
		box = temp;
	} else {
		return false;
	}
	for (int i = 1; i < list.size(); i++) {
		if (list[i] != nullptr && list[i]->boundingBox(t0, t1, temp)) {
			box = surroundBox(box, temp);
		} else {
			return false;
		}
	}
	return true;
}

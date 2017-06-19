//
//  BVH.cpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include <cstdlib>
#include "BVH.hpp"

inline int compareX(const void *a, const void *b) {
	Box leftBox, rightBox;
	Object *ao = *(Object **)a;
	Object *bo = *(Object **)b;
	if (!ao->boundingBox(0, 0, leftBox) || !bo->boundingBox(0, 0, rightBox)) {
		
	}
	if (leftBox.min.x < rightBox.min.x) {
		return -1;
	} else {
		return 1;
	}
}

inline int compareY(const void *a, const void *b) {
	Box leftBox, rightBox;
	Object *ao = *(Object **)a;
	Object *bo = *(Object **)b;
	if (!ao->boundingBox(0, 0, leftBox) || !bo->boundingBox(0, 0, rightBox)) {
		
	}
	if (leftBox.min.y < rightBox.min.y) {
		return -1;
	} else {
		return 1;
	}
}

inline int compareZ(const void *a, const void *b) {
	Box leftBox, rightBox;
	Object *ao = *(Object **)a;
	Object *bo = *(Object **)b;
	if (!ao->boundingBox(0, 0, leftBox) || !bo->boundingBox(0, 0, rightBox)) {
		
	}
	if (leftBox.min.z < rightBox.min.z) {
		return -1;
	} else {
		return 1;
	}
}

BVH::BVH(Object **list, int n, double time0, double time1) {
	int axis = static_cast<int>(3 * drand());
	if (axis == 0) {
		qsort(list, n, sizeof(Object *), compareX);
	} else if (axis == 1) {
		qsort(list, n, sizeof(Object *), compareY);
	} else {
		qsort(list, n, sizeof(Object *), compareZ);
	}
	if (n == 1) {
		left = right = list[0];
	} else if (n == 2) {
		left = list[0];
		right = list[1];
	} else {
		left = new BVH(list, n / 2, time0, time1);
		right = new BVH(list + n / 2, n - n / 2, time0, time1);
	}
	Box leftBox, rightBox;
	if (!left->boundingBox(time0, time1, leftBox) ||
		!right->boundingBox(time0, time1, rightBox)) {}
	box = surroundBox(leftBox, rightBox);
}

bool BVH::hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const {
	if (box.hit(ray, tmin, tmax)) {
		HitRecord leftRecord, rightRecord;
		bool hitLeft = left->hit(ray, tmin, tmax, leftRecord);
		bool hitRight = right->hit(ray, tmin, tmax, rightRecord);
		if (hitLeft && hitRight) {
			record = leftRecord.t < rightRecord.t ? leftRecord : rightRecord;
			return true;
		} else if (hitLeft) {
			record = leftRecord;
			return true;
		} else if (hitRight) {
			record = rightRecord;
			return true;
		}
	}
	return false;
}

bool BVH::boundingBox(double t0, double t1, Box &box) const {
	box = this->box;
	return true;
}

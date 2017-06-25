//
//  BVH.cpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include "BVH.hpp"

inline int compareX(const void *a, const void *b) {
	BBox left_box, right_box;
	Object *ao = *(Object **)a;
	Object *bo = *(Object **)b;
	if (!ao->boundingBox(0, 0, left_box) || !bo->boundingBox(0, 0, right_box)) {
		std::cerr << "No Bouding Box at all." << std::endl;
	}
	if (left_box.min.x < right_box.min.x) {
		return -1;
	} else {
		return 1;
	}
}

inline int compareY(const void *a, const void *b) {
	BBox left_box, right_box;
	Object *ao = *(Object **)a;
	Object *bo = *(Object **)b;
	if (!ao->boundingBox(0, 0, left_box) || !bo->boundingBox(0, 0, right_box)) {
		std::cerr << "No Bouding Box at all." << std::endl;
	}
	if (left_box.min.y < right_box.min.y) {
		return -1;
	} else {
		return 1;
	}
}

inline int compareZ(const void *a, const void *b) {
	BBox left_box, right_box;
	Object *ao = *(Object **)a;
	Object *bo = *(Object **)b;
	if (!ao->boundingBox(0, 0, left_box) || !bo->boundingBox(0, 0, right_box)) {
		std::cerr << "No Bouding Box at all." << std::endl;
	}
	if (left_box.min.z < right_box.min.z) {
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
	BBox left_box, right_box;
	if (!left->boundingBox(time0, time1, left_box) ||
		!right->boundingBox(time0, time1, right_box)) {
		std::cerr << "No Bouding Box at all." << std::endl;
	}
	box = surroundBox(left_box, right_box);
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

bool BVH::boundingBox(double t0, double t1, BBox &box) const {
	box = this->box;
	return true;
}

//
//  BVHNode.h
//  Papaya
//
//  Created by Guo Chen on 6/18/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef BVHNode_h
#define BVHNode_h

#include <cstdlib>
#include <vector>
#include "Object.h"
#include "AABB.h"

using std::vector;

inline int compareX(const void *a, const void *b) {
	AABB leftBox, rightBox;
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
	AABB leftBox, rightBox;
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
	AABB leftBox, rightBox;
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

class BVHNode: public Object {
public:
	AABB box;
	Object *left, *right;
	BVHNode() {}
	BVHNode(Object **list, int n, double time0, double time1) {
		int axis = static_cast<int>(3 * drand48());
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
			left = new BVHNode(list, n / 2, time0, time1);
			right = new BVHNode(list + n / 2, n - n / 2, time0, time1);
		}
		AABB leftBox, rightBox;
		if (!left->boundingBox(time0, time1, leftBox) || !right->boundingBox(time0, time1, rightBox)) {
			
		}
		box = surroundBox(leftBox, rightBox);
	}
	bool hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const {
		if (box.hit(ray, tMin, tMax)) {
			HitRecord leftRec, rightRec;
			bool hitLeft = left->hit(ray, tMin, tMax, leftRec);
			bool hitRight = right->hit(ray, tMin, tMax, rightRec);
			if (hitLeft && hitRight) {
				record = leftRec.t < rightRec.t ? leftRec : rightRec;
				return true;
			} else if (hitLeft) {
				record = leftRec;
				return true;
			} else if (hitRight) {
				record = rightRec;
				return true;
			}
		}
		return false;
	}
	bool boundingBox(double t0, double t1, AABB &box) const {
		box = this->box;
		return true;
	}
};

#endif /* BVHNode_h */

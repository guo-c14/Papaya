//
//  BVH.hpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef BVH_hpp
#define BVH_hpp

#include <cstdlib>
#include <iostream>
#include "Object.hpp"

class BVH: public Object {
protected:
	BBox box;
	Object *left, *right;
public:
	BVH(Object **list, int n, double time0, double time1);
	virtual bool hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const;
	virtual bool boundingBox(double t0, double t1, BBox &box) const;
};

#endif /* BVH_hpp */

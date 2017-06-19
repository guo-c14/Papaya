//
//  BVH.hpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef BVH_hpp
#define BVH_hpp

#include "Box.hpp"
#include "Object.hpp"

class BVH: public Object {
public:
	Box box;
	Object *left, *right;
	BVH(Object **list, int n, double time0, double time1);
	virtual bool hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const;
	virtual bool boundingBox(double t0, double t1, Box &box) const;
};

#endif /* BVH_hpp */

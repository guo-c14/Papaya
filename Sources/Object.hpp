//
//  Object.hpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include "Box.hpp"
#include "HitRecord.hpp"

class Object {
public:
	virtual bool hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const = 0;
	virtual bool boundingBox(double t0, double t1, Box &box) const = 0;
};

#endif /* Object_hpp */

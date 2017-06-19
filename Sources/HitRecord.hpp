//
//  HitRecord.hpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef HitRecord_hpp
#define HitRecord_hpp

#include "Vec3D.hpp"

class Material;

struct HitRecord {
	double t;
	Vec3D p;
	Vec3D normal;
	Material *material;
};

#endif /* HitRecord_hpp */

//
//  Scene.hpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <vector>
#include "Box.hpp"
#include "Object.hpp"

using std::vector;

class Scene {
public:
	vector<Object *> list;
	Scene(vector<Object *> list): list(list) {}
	bool hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const;
	bool boundingBox(double t0, double t1, Box &box) const;
};


#endif /* Scene_hpp */

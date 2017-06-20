//
//  Cube.cpp
//  Papaya
//
//  Created by Guo Chen on 6/21/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include "Cube.hpp"

Cube::Cube(const Vec3D &min, const Vec3D &max, Material *material): min(min),
	max(max) {
	vector<Object *> list(6);
	list[0] = new RectangleXY(min.x, max.x, min.y, max.y, max.z, material);
	list[1] = new FlipNormal(new RectangleXY(min.x, max.x, min.y, max.y, min.z, material));
	list[2] = new RectangleXZ(min.x, max.x, min.z, max.z, max.y, material);
	list[3] = new FlipNormal(new RectangleXY(min.x, max.x, min.y, max.y, min.z, material));
	list[4] = new RectangleYZ(min.y, max.y, min.z, max.z, max.x, material);
	list[5] = new FlipNormal(new RectangleYZ(min.y, max.y, min.z, max.z, min.x, material));
	this->list = new ObjectList(list);
}

bool Cube::hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const {
	return list->hit(ray, tmin, tmax, record);
}

bool Cube::boundingBox(double t0, double t1, BBox &box) const {
	box = BBox(min, max);
	return true;
}

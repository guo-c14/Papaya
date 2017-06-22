//
//  Circle.cpp
//  Papaya
//
//  Created by Guo Chen on 6/22/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include "Circle.hpp"

Circle::Circle(const Vec3D &center, const Vec3D &normal, double radius,
			   Material *material): center(center), normal(normal), radius(radius), material(material) {}

bool Circle::hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const {
	double t = (center.y - ray.origin.y) / ray.direction.y;
	if (t < tmin || t > tmax) {
		return false;
	}
	if (norm2(ray.pointAt(t) - center) >= radius * radius) {
		return false;
	}
	record.t = t;
	record.p = ray.pointAt(t);
	record.material = material;
	record.normal = normal;
	return true;
}

bool Circle::boundingBox(double t0, double t1, BBox &box) const {
	box = BBox({center.x - radius, center.y - 0.0001, center.z - radius}, {center.x + radius, center.y + 0.0001, center.z + radius});
	return true;
}

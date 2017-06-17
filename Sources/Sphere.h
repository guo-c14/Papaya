//
//  Sphere.h
//  Papaya
//
//  Created by Guo Chen on 6/17/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Sphere_h
#define Sphere_h

#include <cmath>
#include "Vector.h"
#include "Object.h"

class Sphere: public Object {
public:
	Vector center;
	double radius;
	Material *material;
	Sphere() {}
	Sphere(Vector center, double radius, Material *material):
		center(center),
		radius(radius),
		material(material) {}
	bool hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const {
		Vector oc = ray.origin - center;
		double a = dot(ray.direction, ray.direction);
		double b = dot(oc, ray.direction);
		double c = dot(oc, oc) - radius * radius;
		double discriminant = b * b - a * c;
		if (discriminant > 0) {
			double temp = (-b - sqrt(discriminant)) / a;
			if (tMin < temp && temp < tMax) {
				record.t = temp;
				record.p = ray.pointAt(record.t);
				record.normal = (record.p - center) / radius;
				record.material = material;
				return true;
			}
			temp = (-b + sqrt(discriminant)) / a;
			if (tMin < temp && temp < tMax) {
				record.t = temp;
				record.p = ray.pointAt(record.t);
				record.normal = (record.p - center) / radius;
				record.material = material;
				return true;
			}
		}
		return false;
	}
};

#endif /* Sphere_h */

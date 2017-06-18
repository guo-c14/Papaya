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
	bool boundingBox(double t0, double t1, AABB &box) const {
		box = AABB(center - radius, center + radius);
		return true;
	}
};

class MovingSphere: public Object {
public:
	Vector center0, center1;
	double time0, time1;
	double radius;
	Material *material;
	MovingSphere() {}
	MovingSphere(Vector center0, Vector center1, double t0, double t1,
				 double radius, Material *material):
	center0(center0),
	center1(center1),
	time0(t0),
	time1(t1),
	radius(radius),
	material(material) {}
	Vector center(double time) const {
		return center0 + (time - time0) / (time1 - time0) * (center1 - center0);
	}
	bool hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const {
		Vector oc = ray.origin - center(ray.time);
		double a = dot(ray.direction, ray.direction);
		double b = dot(oc, ray.direction);
		double c = dot(oc, oc) - radius * radius;
		double discriminant = b * b - a * c;
		if (discriminant > 0) {
			double temp = (-b - sqrt(discriminant)) / a;
			if (tMin < temp && temp < tMax) {
				record.t = temp;
				record.p = ray.pointAt(record.t);
				record.normal = (record.p - center(ray.time)) / radius;
				record.material = material;
				return true;
			}
			temp = (-b + sqrt(discriminant)) / a;
			if (tMin < temp && temp < tMax) {
				record.t = temp;
				record.p = ray.pointAt(record.t);
				record.normal = (record.p - center(ray.time)) / radius;
				record.material = material;
				return true;
			}
		}
		return false;
	}
	bool boundingBox(double t0, double t1, AABB &box) const {
		AABB box0(center0 - radius, center0 + radius);
		AABB box1(center1 - radius, center1 + radius);
		box = surroundBox(box0, box1);
		return true;
	}
};

#endif /* Sphere_h */

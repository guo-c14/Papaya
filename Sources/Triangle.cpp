//
//  Triangle.cpp
//  Papaya
//
//  Created by Guo Chen on 6/22/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include "Triangle.hpp"

Triangle::Triangle(const Vec3D &v0, const Vec3D &v1, const Vec3D &v2,
				   Material *material): vertex{v0, v1, v2}, material(material) {
	normal = cross(v1 - v0, v2 - v0);
}

bool Triangle::hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const {
	Vec3D e1 = v1 - v0;
	Vec3D e2 = v2 - v0;
	Vec3D p = cross(ray.direction, e2);
	double det = dot(e1, p);
	Vec3D t;
	if (det > 0) {
		t = ray.origin - v0;
	} else {
		det = -det;
		t = v0 - ray.origin;
	}
	if (det < tmin || det > tmax) {
		return false;
	}
	double u = dot(t, p);
	if (u < 0 || u > det) {
		return false;
	}
	Vec3D q = cross(t, e1);
	double v = dot(ray.direction, q);
	if (v < 0 || u + v > det) {
		return false;
	}
	double invDet = 1.0 / det;
	record.t = dot(e2, q) * invDet;
	record.u = u * invDet;
	record.v = v * invDet;
	record.p = ray.pointAt(record.t);
	record.material = material;
	record.normal = normal;
	return true;
}

bool Triangle::boundingBox(double t0, double t1, BBox &box) const {
	double x_min, x_max, y_min, y_max, z_min, z_max;
	x_min = v0.x < v1.x ? (v0.x < v2.x ? v0.x : v2.x) : (v1.x < v2.x ? v1.x : v2.x);
	y_min = v0.y < v1.y ? (v0.y < v2.y ? v0.y : v2.y) : (v1.y < v2.y ? v1.y : v2.y);
	z_min = v0.z < v1.z ? (v0.z < v2.z ? v0.z : v2.z) : (v1.z < v2.z ? v1.z : v2.z);
	x_max = v0.x > v1.x ? (v0.x > v2.x ? v0.x : v2.x) : (v1.x > v2.x ? v1.x : v2.x);
	y_max = v0.y > v1.y ? (v0.y > v2.y ? v0.y : v2.y) : (v1.y > v2.y ? v1.y : v2.y);
	z_max = v0.z > v1.z ? (v0.z > v2.z ? v0.z : v2.z) : (v1.z > v2.z ? v1.z : v2.z);
	box = BBox({x_min, y_min, z_min}, {x_max, y_max, z_max});
	return true;
}

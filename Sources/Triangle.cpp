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
	normal = cross(v1 - v0, v2 - v0).normalize();
}

bool Triangle::hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const {
	Vec3D edge1 = v1 - v0;
	Vec3D edge2 = v2 - v0;
	Vec3D pvec = cross(ray.direction, edge2);
	double det = dot(edge1, pvec);
	if (-0.000001 < det && det < 0.000001) {
		return false;
	}
	double inv_det = 1.0 / det;
	Vec3D tvec = ray.origin - v0;
	double u = dot(pvec, tvec) * inv_det;
	if (u < 0 || u > 1) {
		return false;
	}
	Vec3D qvec = cross(tvec, edge1);
	double v = dot(ray.direction, qvec) * inv_det;
	if (v < 0 || u + v > 1) {
		return false;
	}
	double t = dot(edge2, qvec) * inv_det;
	if (t < tmin || t > tmax) {
		return false;
	}
	record.t = t;
	record.p = ray.pointAt(t);
	record.normal = normal;
	record.material = material;
	record.u = u;
	record.v = v;
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
	box = BBox({x_min - 0.0001, y_min - 0.0001, z_min - 0.0001}, {x_max + 0.0001, y_max + 0.0001, z_max + 0.0001});
	return true;
}

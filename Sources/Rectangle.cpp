//
//  Rectangle.cpp
//  Papaya
//
//  Created by Guo Chen on 6/20/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include "Rectangle.hpp"

RectangleXY::RectangleXY(double x0, double x1, double y0, double y1, double k,
	Material *material): x0(x0), x1(x1), y0(y0), y1(y1), k(k),
	material(material){}

bool RectangleXY::hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const {
	double t = (k - ray.origin.z) / ray.direction.z;
	if (t < tmin || t > tmax) {
		return false;
	}
	double x = ray.origin.x + t * ray.direction.x;
	double y = ray.origin.y + t * ray.direction.y;
	if (x < x0 || x > x1 || y < y0 || y > y1) {
		return false;
	}
	record.t = t;
	record.material = material;
	record.p = ray.pointAt(t);
	record.normal = {0, 0, 1};
	return true;
}

bool RectangleXY::boundingBox(double t0, double t1, BBox &box) const {
	box = BBox(Vec3D(x0, y0, k - 0.0001), Vec3D(x1, y1, k + 0.0001));
	return true;
}

RectangleYZ::RectangleYZ(double y0, double y1, double z0, double z1, double k,
	Material *material): y0(y0), y1(y1), z0(z0), z1(z1), k(k),
	material(material){}

bool RectangleYZ::hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const {
	double t = (k - ray.origin.x) / ray.direction.x;
	if (t < tmin || t > tmax) {
		return false;
	}
	double y = ray.origin.y + t * ray.direction.y;
	double z = ray.origin.z + t * ray.direction.z;
	if (y < y0 || y > y1 || z < z0 || z > z1) {
		return false;
	}
	record.t = t;
	record.material = material;
	record.p = ray.pointAt(t);
	record.normal = {1, 0, 0};
	return true;
}

bool RectangleYZ::boundingBox(double t0, double t1, BBox &box) const {
	box = BBox(Vec3D(k - 0.0001, y0, z0), Vec3D(k + 0.0001, y1, z1));
	return true;
}

RectangleXZ::RectangleXZ(double x0, double x1, double z0, double z1, double k,
	Material *material): x0(x0), x1(x1), z0(z0), z1(z1), k(k), material(material){}

bool RectangleXZ::hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const {
	double t = (k - ray.origin.y) / ray.direction.y;
	if (t < tmin || t > tmax) {
		return false;
	}
	double x = ray.origin.x + t * ray.direction.x;
	double z = ray.origin.z + t * ray.direction.z;
	if (x < x0 || x > x1 || z < z0 || z > z1) {
		return false;
	}
	record.t = t;
	record.material = material;
	record.p = ray.pointAt(t);
	record.normal = {0, 1, 0};
	return true;
}

bool RectangleXZ::boundingBox(double t0, double t1, BBox &box) const {
	box = BBox(Vec3D(x0, k - 0.0001, z0), Vec3D(x1, k + 0.0001, z1));
	return true;
}

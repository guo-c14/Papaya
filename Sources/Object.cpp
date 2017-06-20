//
//  Object.cpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include "Object.hpp"

ObjectList::ObjectList(const vector<Object *> &list): list(list) {}

bool ObjectList::hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const {
	HitRecord tempRecord;
	bool hitAnything = false;
	double closest = tmax;
	for (int i = 0; i < list.size(); i++) {
		if (list[i] != nullptr && list[i]->hit(ray, tmin, closest, tempRecord)) {
			hitAnything = true;
			closest = tempRecord.t;
			record = tempRecord;
		}
	}
	return hitAnything;
}

bool ObjectList::boundingBox(double t0, double t1, BBox &box) const {
	if (list.size() < 1) {
		return false;
	}
	BBox temp;
	if (list[0] != nullptr && list[0]->boundingBox(t0, t1, temp)) {
		box = temp;
	} else {
		return false;
	}
	for (int i = 1; i < list.size(); i++) {
		if (list[i] != nullptr && list[i]->boundingBox(t0, t1, temp)) {
			box = surroundBox(box, temp);
		} else {
			return false;
		}
	}
	return true;
}

FlipNormal::FlipNormal(Object *object): object(object) {}

bool FlipNormal::hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const {
	if (object->hit(ray, tmin, tmax, record)) {
		record.normal = -record.normal;
		return true;
	}
	return false;
}

bool FlipNormal::boundingBox(double t0, double t1, BBox &box) const {
	return object->boundingBox(t0, t1, box);
}

Translate::Translate(Object *object, const Vec3D &offset): object(object), offset(offset) {}

bool Translate::hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const {
	Ray translated_ray(ray.origin - offset, ray.direction, ray.time);
	if (object->hit(translated_ray, tmin, tmax, record)) {
		record.p += offset;
		return true;
	}
	return false;
}

bool Translate::boundingBox(double t0, double t1, BBox &box) const {
	if (object->boundingBox(t0, t1, box)) {
		box = BBox(box.min + offset, box.max + offset);
		return true;
	}
	return false;
}

RotateY::RotateY(Object *object, double theta): object(object) {
	theta *= PI_180;
	sin_theta = sin(theta);
	cos_theta = cos(theta);
	exist_bbox = object->boundingBox(0, 1, bbox);
	Vec3D min(MAX_DOUBLE);
	Vec3D max(MIN_DOUBLE);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				double x = i * bbox.max.x + (1 - i) * bbox.min.x;
				double y = j * bbox.max.y + (1 - j) * bbox.min.y;
				double z = k * bbox.max.z + (1 - k) * bbox.min.z;
				double new_x = x * cos_theta + z * sin_theta;
				double new_z = -x * sin_theta + z * cos_theta;
				Vec3D temp(new_x, y, new_z);
				for (int c = 0; c < 3; c++) {
					if (temp[c] > max[c]) {
						max[c] = temp[c];
					}
					if (temp[c] < min[c]) {
						min[c] = temp[c];
					}
				}
			}
		}
	}
	bbox = BBox(min, max);
}

bool RotateY::hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const {
	Vec3D origin, direction;
	origin[0] = cos_theta * ray.origin[0] - sin_theta * ray.origin[2];
	origin[1] = ray.origin[1];
	origin[2] = sin_theta * ray.origin[0] + cos_theta * ray.origin[2];
	direction[0] = cos_theta * ray.direction[0] - sin_theta * ray.direction[2];
	direction[1] = ray.direction[1];
	direction[2] = sin_theta * ray.direction[0] + cos_theta * ray.direction[2];
	Ray rotated_ray(origin, direction, ray.time);
	if (object->hit(rotated_ray, tmin, tmax, record)) {
		Vec3D p, normal;
		p[0] = cos_theta * record.p[0] + sin_theta * record.p[2];
		p[1] = record.p[1];
		p[2] = -sin_theta * record.p[0] + cos_theta * record.p[2];
		normal[0] = cos_theta * record.normal[0] + sin_theta * record.normal[2];
		normal[1] = record.normal[1];
		normal[2] = -sin_theta * record.normal[0] + cos_theta * record.normal[2];
		record.p = p;
		record.normal = normal;
		return true;
	}
	return false;
}

bool RotateY::boundingBox(double t0, double t1, BBox &box) const {
	box = bbox;
	return exist_bbox;
}

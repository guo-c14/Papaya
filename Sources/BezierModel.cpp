//
//  BezierModel.cpp
//  Papaya
//
//  Created by Guo Chen on 6/22/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include <iostream>
#include <Eigen/Dense>
#include "BezierModel.hpp"

using Eigen::Matrix3d;
using Eigen::Vector3d;

BezierModel::BezierModel(const BezierCurve &curve, Material *material): curve(curve), material(material) {
	double x_max, y_min, y_max;
	y_min = MAX_DOUBLE;
	x_max = y_max = MIN_DOUBLE;
	for (const auto item: curve.control_points) {
		if (item.x > x_max) {
			x_max = item.x;
		}
		if (item.y < y_min) {
			y_min = item.y;
		}
		if (item.y > y_max) {
			y_max = item.y;
		}
	}
	bbox = BBox({-x_max, y_min, -x_max}, {x_max, y_max, x_max});
}

bool BezierModel::hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const {
	Vec3D value = (bbox.min + bbox.max) / 2, derivative;
	Vector3d solution;
	Vector3d next_solution {
		(value.x - ray.origin.x) / ray.direction.x,
		drand(),
		2 * drand() * PI
	};
	Vector3d A(ray.origin.x, ray.origin.y, ray.origin.z);
	Vector3d B(ray.direction.x, ray.direction.y, ray.direction.z);
	Vector3d delta(1, 1, 1);
	Vector3d F;
	Matrix3d matrix;
	matrix(0, 0) = ray.direction.x;
	matrix(1, 0) = ray.direction.y;
	matrix(2, 0) = ray.direction.z;
	matrix(1, 2) = 0;
	int depth = 0;
	while (depth < 100 && delta.dot(delta) >= 0.0001) {
		solution = next_solution;
		value = curve.pointAt(solution[1]);
		derivative = curve.tangent(solution[1]);
		matrix(0, 1) = -derivative.x * cos(solution[2]);
		matrix(0, 2) = value.x * sin(solution[2]);
		matrix(1, 1) = -derivative.y;
		matrix(2, 1) = derivative.x * sin(solution[2]);
		matrix(2, 2) = value.x * cos(solution[2]);
		F = A + B * solution[0];
		F[0] -= value.x * cos(solution[2]);
		F[1] -= value.y;
		F[2] += value.x * sin(solution[2]);
		next_solution = solution - matrix.inverse().eval() * F;
		if (next_solution[1] > 1 || next_solution[1] < 0) {
			next_solution[1] = drand();
		}
		delta = next_solution - solution;
		depth++;
	}
	if (depth == 100 || std::isnan(delta.dot(delta))) {
		return false;
	}
	if (dot(ray.direction, normalAt(next_solution[1], next_solution[2])) >= 0) {
		depth = 0;
		next_solution = {next_solution[0] * 0.5, 1 - next_solution[1], next_solution[2] + PI};
		while (depth < 100 && delta.dot(delta) >= 0.0001) {
			solution = next_solution;
			value = curve.pointAt(solution[1]);
			derivative = curve.tangent(solution[1]);
			matrix(0, 1) = -derivative.x * cos(solution[2]);
			matrix(0, 2) = value.x * sin(solution[2]);
			matrix(1, 1) = -derivative.y;
			matrix(2, 1) = derivative.x * sin(solution[2]);
			matrix(2, 2) = value.x * cos(solution[2]);
			F = A + B * solution[0];
			F[0] -= value.x * cos(solution[2]);
			F[1] -= value.y;
			F[2] += value.x * sin(solution[2]);
			next_solution = solution - matrix.inverse().eval() * F;
			if (next_solution[1] > 1 || next_solution[1] < 0) {
				next_solution[1] = drand();
			}
			delta = next_solution - solution;
			depth++;
		}
	}
	if (depth == 100 || std::isnan(delta.dot(delta))) {
		return false;
	}
	if (tmin < next_solution[0] && next_solution[0] < tmax)  {
		while (next_solution[2] < 0) {
			next_solution[2] += PI_2;
		}
		while (next_solution[2] > PI_2) {
			next_solution[2] -= PI_2;
		}
		record.t = next_solution[0];
		record.p = ray.pointAt(next_solution[0]);
		record.normal = normalAt(next_solution[1], next_solution[2]);
		record.material = material;
		record.u = next_solution[2] / PI_2;
		record.v = 1 - next_solution[1];
		return true;
	}
	return false;
}

bool BezierModel::boundingBox(double t0, double t1, BBox &box) const {
	box = bbox;
	return true;
}

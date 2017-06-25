//
//  BezierModel.hpp
//  Papaya
//
//  Created by Guo Chen on 6/22/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef BezierModel_hpp
#define BezierModel_hpp

#include <Eigen/Dense>
#include "Object.hpp"
#include "BezierCurve.hpp"
#include "Material.hpp"

using Eigen::Matrix3d;
using Eigen::Vector3d;

class BezierModel: public Object {
protected:
	BBox bbox;
	BezierCurve curve;
	Material *material;
public:
	BezierModel(const BezierCurve &curve, Material *material);
	Vec3D pointAt(double u, double v) const;
	Vec3D normalAt(double u, double v) const;
	virtual bool hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const;
	virtual bool boundingBox(double t0, double t1, BBox &box) const;
};

inline Vec3D BezierModel::pointAt(double u, double v) const {
	Vec3D temp = curve.pointAt(u);
	return {temp.x * cos(v), temp.y, -temp.x * sin(v)};
}

inline Vec3D BezierModel::normalAt(double u, double v) const {
	Vec3D temp = curve.tangent(u);
	temp.z = -temp.x * sin(v);
	temp.x *= cos(v);
	Vec3D temp1{-sin(v), 0, -cos(v)};
	return normalize(cross(temp1, temp));
}

#endif /* BezierModel_hpp */

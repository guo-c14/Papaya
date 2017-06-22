//
//  BezierCurve.hpp
//  Papaya
//
//  Created by Guo Chen on 6/21/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef BezierCurve_hpp
#define BezierCurve_hpp

#include <vector>
#include "Utility.hpp"

using std::vector;

class BezierCurve {
public:
	int degree;
	vector<Vec3D> control_points;
	BezierCurve(const vector<Vec3D> &control_points);
	BezierCurve(const BezierCurve &curve);
	BezierCurve &operator=(const BezierCurve &curve);
	Vec3D pointAt(double t) const;
	Vec3D operator[](double t) const;
	Vec3D tangent(double t) const;
};

inline BezierCurve &BezierCurve::operator=(const BezierCurve &curve) {
	degree = curve.degree;
	control_points = curve.control_points;
	return *this;
}

inline Vec3D BezierCurve::pointAt(double t) const {
	Vec3D result;
	for (int i = 0; i < control_points.size(); i++) {
		result += control_points[i] * bernstein(degree, i, t);
	}
	return result;
}

inline Vec3D BezierCurve::operator[](double t) const {
	return pointAt(t);
}

inline Vec3D BezierCurve::tangent(double t) const {
	if (t == 0) {
		return control_points[1] - control_points[0];
	} else if (t + 0.0000000001 >= 1) {
		return control_points[degree] - control_points[degree - 1];
	} else {
		return pointAt(t + 0.0000000001) * 10000000000.0 - pointAt(t) * 10000000000.0;
	}
}

#endif /* BezierCurve_hpp */

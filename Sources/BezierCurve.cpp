//
//  BezierCurve.cpp
//  Papaya
//
//  Created by Guo Chen on 6/21/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include "BezierCurve.hpp"

BezierCurve::BezierCurve(const vector<Vec3D> &control_points): control_points(control_points) {
	degree = static_cast<int>(control_points.size()) - 1;
}

BezierCurve::BezierCurve(const BezierCurve &curve) {
	*this = curve;
}

//
//  Light.cpp
//  Papaya
//
//  Created by Guo Chen on 6/20/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include "Light.hpp"

DiffuseLight::DiffuseLight(const Vec3D &color): color(color) {}

bool DiffuseLight::scatter(const Ray &incident, const HitRecord &record,
						   Vec3D &attenuation, Ray &scattered) const {
	return false;
}

Vec3D DiffuseLight::emitRay() const {
	return color;
}

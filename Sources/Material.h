//
//  Material.h
//  Papaya
//
//  Created by Guo Chen on 6/17/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Material_h
#define Material_h

#include "Vector.h"
#include "Ray.h"
#include "Object.h"

class Material  {
public:
	virtual bool scatter(const Ray& r_in, const HitRecord &rec, Vector &attenuation, Ray &scattered) const = 0;
};

class Diffuse: public Material {
public:
	Vector albedo;
	Diffuse(const Vector &a) : albedo(a) {}
	bool scatter(const Ray& r_in, const HitRecord &rec, Vector &attenuation, Ray &scattered) const {
		Vector target = rec.p + rec.normal + random_in_unit_sphere();
		scattered = Ray(rec.p, target - rec.p);
		attenuation = albedo;
		return true;
	}
};

class Metal : public Material {
public:
	Vector albedo;
	double fuzz;
	Metal(const Vector &a, double f) : albedo(a), fuzz(f < 1.0 ? f : 1.0) {}
	bool scatter(const Ray &r_in, const HitRecord &rec, Vector &attenuation, Ray &scattered) const {
		Vector reflected = reflect(r_in.direction, rec.normal);
		scattered = Ray(rec.p, reflected + fuzz * random_in_unit_sphere());
		attenuation = albedo;
		return dot(scattered.direction, rec.normal) > 0;
	}
	
};

#endif /* Material_h */

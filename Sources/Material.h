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
	virtual bool scatter(const Ray &r_in, const HitRecord &rec, Vector &attenuation, Ray &scattered) const = 0;
};

class Diffuse: public Material {
public:
	Vector albedo;
	Diffuse(const Vector &a) : albedo(a) {}
	bool scatter(const Ray &r_in, const HitRecord &rec, Vector &attenuation, Ray &scattered) const {
		Vector target = rec.p + rec.normal + random_in_unit_sphere();
		scattered = Ray(rec.p, target - rec.p, r_in.time);
		attenuation = albedo;
		return true;
	}
};

class Metal: public Material {
public:
	Vector albedo;
	double fuzz;
	Metal(const Vector &a, double f) : albedo(a), fuzz(f < 1.0 ? f : 1.0) {}
	bool scatter(const Ray &r_in, const HitRecord &rec, Vector &attenuation, Ray &scattered) const {
		Vector reflected = reflect(r_in.direction, rec.normal);
		scattered = Ray(rec.p, reflected + fuzz * random_in_unit_sphere(), r_in.time);
		attenuation = albedo;
		return dot(scattered.direction, rec.normal) > 0;
	}
};

class Dielectric: public Material {
public:
	double ref_idx;
	Dielectric(double ri) : ref_idx(ri) {}
	virtual bool scatter(const Ray &r_in, const HitRecord &rec, Vector &attenuation, Ray &scattered) const  {
		Vector outward_normal;
		Vector reflected = reflect(r_in.direction, rec.normal);
		double ni_over_nt;
		attenuation = Vector(1.0, 1.0, 1.0);
		Vector refracted;
		double reflect_prob;
		double cosine;
		if (dot(r_in.direction, rec.normal) > 0) {
			outward_normal = -rec.normal;
			ni_over_nt = ref_idx;
			cosine = dot(r_in.direction, rec.normal) / norm(r_in.direction);
			cosine = sqrt(1 - ref_idx * ref_idx * (1 - cosine * cosine));
		}
		else {
			outward_normal = rec.normal;
			ni_over_nt = 1.0 / ref_idx;
			cosine = -dot(r_in.direction, rec.normal) / norm(r_in.direction);
		}
		if (refract(r_in.direction, outward_normal, ni_over_nt, refracted))
			reflect_prob = schlick(cosine, ref_idx);
		else
			reflect_prob = 1.0;
		if (drand48() < reflect_prob)
			scattered = Ray(rec.p, reflected, r_in.time);
		else
			scattered = Ray(rec.p, refracted, r_in.time);
		return true;
	}
};


#endif /* Material_h */

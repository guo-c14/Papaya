//
//  Material.cpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include "Material.hpp"

bool Diffuse::scatter(const Ray &r_in, const HitRecord &rec, Vec3D &attenuation, Ray &scattered) const {
	Vec3D target = rec.p + rec.normal + random_in_unit_sphere();
	scattered = Ray(rec.p, target - rec.p, r_in.time);
	attenuation = albedo->value(0, 0, rec.p);
	return true;
}

bool Metal::scatter(const Ray &r_in, const HitRecord &rec, Vec3D &attenuation, Ray &scattered) const {
	Vec3D reflected = reflect(r_in.direction, rec.normal);
	scattered = Ray(rec.p, reflected + fuzz * random_in_unit_sphere(), r_in.time);
	attenuation = albedo;
	return dot(scattered.direction, rec.normal) > 0;
}

bool Dielectric::scatter(const Ray &r_in, const HitRecord &rec, Vec3D &attenuation, Ray &scattered) const  {
	Vec3D outward_normal;
	Vec3D reflected = reflect(r_in.direction, rec.normal);
	double ni_over_nt;
	attenuation = Vec3D(1.0, 1.0, 1.0);
	Vec3D refracted;
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
	if (drand() < reflect_prob)
		scattered = Ray(rec.p, reflected, r_in.time);
	else
		scattered = Ray(rec.p, refracted, r_in.time);
	return true;
}

//
//  Material.cpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include "Utility.hpp"
#include "Material.hpp"

Diffuse::Diffuse(const Vec3D &v) {
	texture = new ConstantTexture(v);
}

Diffuse::Diffuse(Texture *texture): texture(texture) {}

bool Diffuse::scatter(const Ray &incident, const HitRecord &record,
	Vec3D &attenuation, Ray &scattered) const {
	Vec3D target = record.p + record.normal + random_in_unit_sphere();
	scattered = Ray(record.p, target - record.p, incident.time);
	attenuation = texture->value(0, 0, record.p);
	return true;
}

Metal::Metal(const Vec3D &albedo, double fuzz): albedo(albedo),
	fuzz(fuzz < 1.0 ? fuzz : 1.0) {}

bool Metal::scatter(const Ray &incident, const HitRecord &record,
	Vec3D &attenuation, Ray &scattered) const {
	Vec3D reflected = reflect(incident.direction, record.normal);
	scattered = Ray(record.p, reflected + fuzz * random_in_unit_sphere(), incident.time);
	attenuation = albedo;
	return dot(scattered.direction, record.normal) > 0;
}

Dielectric::Dielectric(double ref_idx): ref_idx(ref_idx) {}

bool Dielectric::scatter(const Ray &incident, const HitRecord &record,
	Vec3D &attenuation, Ray &scattered) const  {
	attenuation = 1;
	Vec3D reflected = reflect(incident.direction, record.normal);
	Vec3D refracted;
	Vec3D outward_normal;
	double cosine;
	double ni_over_nt;
	double reflect_prob;
	if (dot(incident.direction, record.normal) > 0) {
		outward_normal = -record.normal;
		ni_over_nt = ref_idx;
		cosine = dot(incident.direction, record.normal) / norm(incident.direction);
		cosine = sqrt(1 - ref_idx * ref_idx * (1 - cosine * cosine));
	}
	else {
		outward_normal = record.normal;
		ni_over_nt = 1.0 / ref_idx;
		cosine = -dot(incident.direction, record.normal) / norm(incident.direction);
	}
	if (refract(incident.direction, outward_normal, ni_over_nt, refracted)) {
		double r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = r0 * r0;
		reflect_prob = r0 + (1 - r0) * pow((1 - cosine), 5);
	}
	else
		reflect_prob = 1.0;
	if (drand() < reflect_prob)
		scattered = Ray(record.p, reflected, incident.time);
	else
		scattered = Ray(record.p, refracted, incident.time);
	return true;
}
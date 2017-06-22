//
//  Material.cpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include "Utility.hpp"
#include "Material.hpp"

Vec3D Material::emitRay() const {
	return 0;
}

Diffuse::Diffuse(const Vec3D &v): texture(new ConstantTexture(v)) {}

Diffuse::Diffuse(Texture *texture): texture(texture) {}

bool Diffuse::scatter(const Ray &incident, const HitRecord &record,
	Vec3D &attenuation, Ray &scattered) const {
	Vec3D target = record.p + record.normal + random_in_unit_sphere();
	scattered = Ray(record.p, target - record.p, incident.time);
	attenuation = texture->value(record.u, record.v, record.p);
	return true;
}

Metal::Metal(const Vec3D &v, double fuzz): texture(new ConstantTexture(v)),
	fuzz(fuzz < 1.0 ? fuzz : 1.0) {}

Metal::Metal(Texture *texture, double fuzz): texture(texture),
	fuzz(fuzz < 1.0 ? fuzz : 1.0) {}

bool Metal::scatter(const Ray &incident, const HitRecord &record,
	Vec3D &attenuation, Ray &scattered) const {
	Vec3D reflected = reflect(incident.direction, record.normal);
	scattered = Ray(record.p, reflected + fuzz * random_in_unit_sphere(), incident.time);
	attenuation = texture->value(record.u, record.v, record.p);
	return dot(scattered.direction, record.normal) > 0;
}

Dielectric::Dielectric(double ref_idx, const Vec3D &color): ref_idx(ref_idx), color(color) {}

bool Dielectric::scatter(const Ray &incident, const HitRecord &record,
	Vec3D &attenuation, Ray &scattered) const  {
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
	if (drand() < reflect_prob) {
		attenuation = 1;
		scattered = Ray(record.p, reflected, incident.time);
	}
	else {
		attenuation = color;
		scattered = Ray(record.p, refracted, incident.time);
	}
	return true;
}

GeneralMaterial::GeneralMaterial(const Vec3D &proportion, const Vec3D &reflect_color, double fuzz, const Vec3D &refract_color, double ref_idx): proportion(proportion), texture(new ConstantTexture(reflect_color)), fuzz(fuzz), refract_color(refract_color), ref_idx(ref_idx) {
	this->proportion /= (proportion.x + proportion.y + proportion.z);
}

GeneralMaterial::GeneralMaterial(const Vec3D &proportion, Texture *texture, double fuzz, const Vec3D &refract_color, double ref_idx): proportion(proportion), texture(texture), fuzz(fuzz), refract_color(refract_color), ref_idx(ref_idx) {
	this->proportion /= (proportion.x + proportion.y + proportion.z);
}

bool GeneralMaterial::scatter(const Ray &incident, const HitRecord &record,
							  Vec3D &attenuation, Ray &scattered) const {
	double rand_num = drand();
	if (rand_num < proportion.x) {
		Vec3D target = record.p + record.normal + random_in_unit_sphere();
		scattered = Ray(record.p, target - record.p, incident.time);
		attenuation = texture->value(record.u, record.v, record.p);
		return true;
	} else if (rand_num < proportion.x + proportion.y) {
		Vec3D reflected = reflect(incident.direction, record.normal);
		scattered = Ray(record.p, reflected + fuzz * random_in_unit_sphere(), incident.time);
		attenuation = texture->value(record.u, record.v, record.p);
		return dot(scattered.direction, record.normal) > 0;
	} else {
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
		if (drand() < reflect_prob) {
			attenuation = texture->value(record.u, record.v, record.p);
			scattered = Ray(record.p, reflected, incident.time);
		}
		else {
			attenuation = refract_color;
			scattered = Ray(record.p, refracted, incident.time);
		}
		return true;
	}
}

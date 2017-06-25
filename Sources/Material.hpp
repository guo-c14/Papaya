//
//  Material.hpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

#include "HitRecord.hpp"
#include "Ray.hpp"
#include "Texture.hpp"

class Material  {
public:
	virtual bool scatter(const Ray &incident, const HitRecord &record,
		Vec3D &attenuation, Ray &scattered) const = 0;
	virtual Vec3D emitRay() const;
};

class Diffuse: public Material {
protected:
	Texture *texture;
public:
	Diffuse(const Vec3D &v);
	Diffuse(Texture *texture);
	virtual bool scatter(const Ray &incident, const HitRecord &record,
		Vec3D &attenuation, Ray &scattered) const;
};

class Metal: public Material {
protected:
	Texture *texture;
	double fuzz;
public:
	Metal(const Vec3D &albedo, double fuzz);
	Metal(Texture *texture, double fuzz);
	virtual bool scatter(const Ray &incident, const HitRecord &record,
		Vec3D &attenuation, Ray &scattered) const;
};

class Dielectric: public Material {
protected:
	double ref_idx;
	Vec3D color;
public:
	Dielectric(double ref_idx, const Vec3D &color = 1);
	virtual bool scatter(const Ray &incident, const HitRecord &record,
		Vec3D &attenuation, Ray &scattered) const;
};

class GeneralMaterial: public Material {
protected:
	Vec3D proportion;
	Texture *texture;
	double fuzz;
	Vec3D refract_color;
	double ref_idx;
public:
	GeneralMaterial(const Vec3D &proportion, const Vec3D &reflect_color, double fuzz, const Vec3D &refract_color, double ref_idx);
	GeneralMaterial(const Vec3D &proportion, Texture *texture, double fuzz, const Vec3D &refract_color, double ref_idx);
	virtual bool scatter(const Ray &incident, const HitRecord &record,
		Vec3D &attenuation, Ray &scattered) const;
};

#endif /* Material_hpp */

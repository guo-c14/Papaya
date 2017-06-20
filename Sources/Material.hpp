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
	Vec3D albedo;
	double fuzz;
public:
	Metal(const Vec3D &albedo, double fuzz);
	virtual bool scatter(const Ray &incident, const HitRecord &record,
		Vec3D &attenuation, Ray &scattered) const;
};

class Dielectric: public Material {
protected:
	double ref_idx;
public:
	Dielectric(double ref_idx);
	virtual bool scatter(const Ray &incident, const HitRecord &record,
		Vec3D &attenuation, Ray &scattered) const;
};

#endif /* Material_hpp */

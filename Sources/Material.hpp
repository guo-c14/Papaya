//
//  Material.hpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

#include "Object.hpp"
#include "Ray.hpp"
#include "Texture.hpp"

class Material  {
public:
	virtual bool scatter(const Ray &r_in, const HitRecord &rec, Vec3D &attenuation, Ray &scattered) const = 0;
};

class Diffuse: public Material {
public:
	Texture *albedo;
	Diffuse(Texture *a) : albedo(a) {}
	virtual bool scatter(const Ray &r_in, const HitRecord &rec, Vec3D &attenuation, Ray &scattered) const;
};

class Metal: public Material {
public:
	Vec3D albedo;
	double fuzz;
	Metal(const Vec3D &a, double f) : albedo(a), fuzz(f < 1.0 ? f : 1.0) {}
	virtual bool scatter(const Ray &r_in, const HitRecord &rec, Vec3D &attenuation, Ray &scattered) const;
};

class Dielectric: public Material {
public:
	double ref_idx;
	Dielectric(double ri) : ref_idx(ri) {}
	virtual bool scatter(const Ray &r_in, const HitRecord &rec, Vec3D &attenuation, Ray &scattered) const;
};

#endif /* Material_hpp */

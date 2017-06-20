//
//  Light.hpp
//  Papaya
//
//  Created by Guo Chen on 6/20/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Light_hpp
#define Light_hpp

#include "Material.hpp"

class DiffuseLight: public Material {
	Vec3D color;
public:
	DiffuseLight(const Vec3D &color);
	virtual bool scatter(const Ray &incident, const HitRecord &record,
						 Vec3D &attenuation, Ray &scattered) const;
	virtual Vec3D emitRay() const;
};

#endif /* Light_hpp */

//
//  Texture.hpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include "Vec3D.hpp"

class Texture {
public:
	virtual Vec3D value(double u, double v, const Vec3D &p) const = 0;
};

class ConstantTexture: public Texture {
public:
	Vec3D color;
	ConstantTexture(Vec3D color);
	virtual Vec3D value(double u, double v, const Vec3D &p) const;
};

class CheckerTexture: public Texture {
public:
	Texture *odd;
	Texture *even;
	double ratio;
	CheckerTexture(Texture *odd, Texture *even, double ratio = 2.0);
	virtual Vec3D value(double u, double v, const Vec3D &p) const;
};

#endif /* Texture_hpp */

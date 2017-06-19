//
//  Vec3D.hpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Vec3D_hpp
#define Vec3D_hpp

#include <cmath>
#include "Utility.hpp"

class Vec3D {
public:
	double elem[3];
	double &x = elem[0];
	double &y = elem[1];
	double &z = elem[2];
	
	Vec3D(double d = 0.0);
	Vec3D(double x, double y, double z);
	Vec3D(const Vec3D &v);
	
	Vec3D &operator=(const Vec3D &v);
	Vec3D &operator+=(const Vec3D &v);
	Vec3D &operator-=(const Vec3D &v);
	Vec3D &operator*=(const Vec3D &v);
	Vec3D &operator/=(const Vec3D &v);
	
	Vec3D operator-() const;
	
	double operator[](int index) const;
	double &operator[](int index);
	
	double norm() const;
	double norm2() const;
	Vec3D &normalize();
};

inline Vec3D &Vec3D::operator=(const Vec3D &v) {
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

inline Vec3D &Vec3D::operator+=(const Vec3D &v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

inline Vec3D &Vec3D::operator-=(const Vec3D &v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

inline Vec3D &Vec3D::operator*=(const Vec3D &v) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

inline Vec3D &Vec3D::operator/=(const Vec3D &v) {
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}
inline Vec3D Vec3D::operator-() const {
	return {-x, -y, -z};
}

inline double Vec3D::operator[](int index) const {
	return elem[index];
}

inline double &Vec3D::operator[](int index) {
	return elem[index];
}

inline double Vec3D::norm() const {
	return sqrt(x * x + y * y + z * z);
}

inline double Vec3D::norm2() const {
	return x * x + y * y + z * z;
}

inline Vec3D &Vec3D::normalize() {
	return *this /= norm();
}

inline Vec3D operator+(const Vec3D &v1, const Vec3D &v2) {
	return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

inline Vec3D operator-(const Vec3D &v1, const Vec3D &v2) {
	return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

inline Vec3D operator*(const Vec3D &v1, const Vec3D &v2) {
	return {v1.x * v2.x, v1.y * v2.y, v1.z * v2.z};
}

inline Vec3D operator/(const Vec3D &v1, const Vec3D &v2) {
	return {v1.x / v2.x, v1.y / v2.y, v1.z / v2.z};
}

inline double dot(const Vec3D &v1, const Vec3D &v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline Vec3D cross(const Vec3D &v1, const Vec3D &v2) {
	return {
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	};
}

inline double norm(const Vec3D &v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline double norm2(const Vec3D &v) {
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

inline double distance(const Vec3D &v1, const Vec3D &v2) {
	return norm(v1 - v2);
}

inline double distance2(const Vec3D &v1, const Vec3D &v2) {
	return norm2(v1 - v2);
}

inline Vec3D normalize(const Vec3D &v) {
	return v / norm(v);
}

inline double schlick(double cosine, double ref_idx) {
	double r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1.0 - r0) * pow((1.0 - cosine), 5);
}

inline bool refract(const Vec3D &v, const Vec3D &n, double ni_over_nt, Vec3D &refracted) {
	Vec3D uv = normalize(v);
	double dt = dot(uv, n);
	double discriminant = 1.0 - ni_over_nt * ni_over_nt * (1.0 - dt * dt);
	if (discriminant > 0.0) {
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}
	else
		return false;
}

inline Vec3D reflect(const Vec3D &v, const Vec3D &n) {
	return v - 2.0 * dot(v, n) * n;
}

inline Vec3D random_in_unit_sphere() {
	Vec3D p;
	do {
		p = 2.0 * Vec3D(drand(), drand(), drand()) - 1.0;
	} while (p.norm2() >= 1.0);
	return p;
}

inline Vec3D random_in_unit_disk() {
	Vec3D p;
	do {
		p = 2.0 * Vec3D(drand(), drand(), 0.0) - Vec3D(1.0, 1.0, 0.0);
	} while (dot(p, p) >= 1.0);
	return p;
}

#endif /* Vec3D_hpp */

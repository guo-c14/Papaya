//
//  Vector.h
//  Papaya
//
//  Created by Guo Chen on 6/17/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Vector_h
#define Vector_h

#include <cmath>
#include <ostream>

using std::ostream;

class Vector {
public:
	double element[3];
	double &x = element[0];
	double &y = element[1];
	double &z = element[2];
	Vector(double d = 0): element{d, d, d} {}
	Vector(double x, double y, double z): element{x, y, z} {}
	Vector(const Vector &v): element{v.x, v.y, v.z} {}
	double operator[](int index) const {
		return element[index];
	}
	double &operator[](int index) {
		return element[index];
	}
	Vector operator+() const {
		return Vector(x, y, z);
	}
	Vector operator-() const {
		return Vector(-x, -y, -z);
	}
	Vector &operator=(const Vector &v) {
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}
	Vector &operator+=(const Vector &v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	Vector &operator-=(const Vector &v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	Vector &operator*=(const Vector &v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}
	Vector &operator/=(const Vector &v) {
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}
	double dot(const Vector &v) const {
		return x * v.x + y * v.y + z * v.z;
	}
	Vector &cross(const Vector &v) {
		Vector temp(*this);
		x = temp.y * v.z - temp.z * v.y;
		y = temp.z * v.x - temp.x * v.z;
		z = temp.x * v.y - temp.y * v.x;
		return *this;
	}
	double norm() const {
		return sqrt(x * x + y * y + z * z);
	}
	double norm2() const {
		return x * x + y * y + z * z;
	}
	double distance(const Vector &v) const {
		return Vector(x - v.x, y - v.y, z - v.z).norm();
	}
	double distance2(const Vector &v) const {
		return Vector(x - v.x, y - v.y, z - v.z).norm2();
	}
	Vector &normalize() {
		return *this /= norm();
	}
};

inline Vector operator+(const Vector &v1, const Vector &v2) {
	return Vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline Vector operator-(const Vector &v1, const Vector &v2) {
	return Vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline Vector operator*(const Vector &v1, const Vector &v2) {
	return Vector(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

inline Vector operator/(const Vector &v1, const Vector &v2) {
	return Vector(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

inline double dot(const Vector &v1, const Vector &v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline Vector cross(const Vector &v1, const Vector &v2) {
	return Vector(v1.y * v2.z - v1.z * v2.y,
				  v1.z * v2.x - v1.x * v2.z,
				  v1.x * v2.y - v1.y * v2.x);
}

inline double norm(const Vector &v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline double norm2(const Vector &v) {
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

inline double distance(const Vector &v1, const Vector &v2) {
	return norm(v1 - v2);
}

inline double distance2(const Vector &v1, const Vector &v2) {
	return norm2(v1 - v2);
}

inline Vector normalize(const Vector &v) {
	return v / norm(v);
}

inline ostream &operator<<(ostream &os, const Vector &v) {
	os << "Vector[" << v.x << ", " << v.y << ", " << v.z << "]";
	return os;
}

#endif /* Vector_h */

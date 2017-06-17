//
//  main.cpp
//  Papaya
//
//  Created by Guo Chen on 6/17/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>
#include "Vector.h"
#include "Object.h"
#include "Sphere.h"
#include "Ray.h"
#include "Camera.h"
#include "Canvas.h"

using std::vector;

Vector random_in_unit_sphere() {
	Vector p;
	do {
		p = 2.0 * Vector(drand48(), drand48(), drand48()) - 1.0;
	} while (p.norm2() >= 1.0);
	return p;
}

Pixel color(const Ray& r, Object *world) {
	HitRecord rec;
	if (world->hit(r, 0.001, 0x1.fffffep+127f, rec)) {
		Vector target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5 * color(Ray(rec.p, target - rec.p), world);
	}
	else {
		double t = 0.5 * r.direction.y + 0.5;
		return (1.0 - t) * Vector(1.0, 1.0, 1.0) + t * Vector(0.5, 0.7, 1.0);
	}
}

int main(int argc, const char * argv[]) {
	Vector low_left_corner(-2.0, -1.0, -1.0);
	Vector horizontal(4.0, 0.0, 0.0);
	Vector vertical(0.0, 2.0, 0.0);
	Vector origin(0.0, 0.0, 0.0);
	vector<Object *> list{
		new Sphere({0.0, 0.0, -4.0}, 2.0),
		new Sphere({0.0, -402, -4.0}, 400.0)
	};
	Object *world = new ObjectList(list);
	int width = 800;
	int height = 400;
	int ns = 100;
	Camera camera;
	Canvas canvas;
	canvas.pixels = vector<vector<Pixel>>(height);
	for (int i = 0; i < height; i++) {
		canvas.pixels[i] = vector<Pixel>(width);
		for (int j = 0; j < width; j++) {
			Pixel col;
			for (int k = 0; k < ns; k++) {
				double u = static_cast<double>(j + drand48()) / width;
				double v = 1.0 - static_cast<double>(i + drand48()) / height;
				Ray r(camera.getRay(u, v));
				col += color(r, world);
			}
			col /= ns;
			canvas.pixels[i][j] = {sqrt(col.x), sqrt(col.y), sqrt(col.z)};
		}
	}
	canvas.setImageFormat(ppm);
	canvas.exportTo("../../../Outputs/1.ppm");
	return 0;
}

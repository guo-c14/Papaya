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
#include "Material.h"

using std::vector;

Pixel color(const Ray &r, Object *world, int depth) {
	HitRecord rec;
	if (world->hit(r, 0.001, 0x1.fffffep+127f, rec)) {
		Vector attenutation;
		Ray scattered;
		if (depth < 50 && rec.material->scatter(r, rec, attenutation, scattered)) {
			return attenutation * color(scattered, world, depth + 1);
		} else {
			return 0;
		}
	}
	else {
		double t = 0.5 * r.direction.y + 0.5;
		return (1.0 - t) * Vector(1.0, 1.0, 1.0) + t * Vector(0.5, 0.7, 1.0);
	}
}

ObjectList *random_scene() {
	vector<Object *> list(500);
	list[0] =  new Sphere(Vector(0, -4000, 0), 4000, new Diffuse(Vector(0.5, 0.5, 0.5)));
	int i = 1;
	for (int a = -10; a < 10; a++) {
		for (int b = -10; b < 10; b++) {
			float choose_mat = drand48();
			Vector center(4 * a + 3.6 * drand48(), 0.8, 4 * b + 3.6 * drand48());
			if (distance(center, {16, 0.8, 0}) > 3.6) {
				if (choose_mat < 0.4) {
					list[i++] = new Sphere(center, 0.8, new Diffuse(Vector(drand48() * drand48(), drand48() * drand48(), drand48() * drand48())));
				}
				else if (choose_mat < 0.8) {
					list[i++] = new MovingSphere(center, center + Vector(0, 2.0 * drand48(), 0), 0.0, 1.0, 0.8, new Diffuse(Vector(drand48() * drand48(), drand48() * drand48(), drand48() * drand48())));
				}
				else if (choose_mat < 0.88) {
					list[i++] = new Sphere(center, 0.8, new Metal(Vector(0.5 * (1 + drand48()), 0.5 * (1 + drand48()), 0.5 * (1 + drand48())), 0.5 * drand48()));
				}
				else if (choose_mat < 0.96) {
					list[i++] = new MovingSphere(center, center + Vector(0, 2.0 * drand48(), 0), 0.0, 1.0, 0.8, new Metal(Vector(0.5 * (1 + drand48()), 0.5 * (1 + drand48()), 0.5 * (1 + drand48())), 0.5 * drand48()));
				}
				else if (choose_mat < 0.98)  {
					list[i++] = new Sphere(center, 0.8, new Dielectric(1.5));
				} else {
					list[i++] = new MovingSphere(center, center + Vector(0, 2.0 * drand48(), 0), 0.0, 1.0, 0.8, new Dielectric(1.5));
				}
			}
		}
	}
	list[i++] = new Sphere(Vector(0, 4, 0), 4.0, new Dielectric(1.5));
	list[i++] = new Sphere(Vector(-16, 4, 0), 4.0, new Diffuse(Vector(0.4, 0.2, 0.1)));
	list[i++] = new Sphere(Vector(16, 4, 0), 4.0, new Metal(Vector(0.7, 0.6, 0.5), 0.0));
	return new ObjectList(list);
}

int main(int argc, const char * argv[]) {
	Vector low_left_corner(-2.0, -1.0, -1.0);
	Vector horizontal(4.0, 0.0, 0.0);
	Vector vertical(0.0, 2.0, 0.0);
	Vector origin(0.0, 0.0, 0.0);
//	vector<Object *> list{
//		new Sphere({0.0, 0.0, -4.0}, 2.0, new Metal({0.8, 0.6, 0.8}, 0.3)),
//		new Sphere({4.0, 0.0, -4.0}, 2.0, new Diffuse({0.3, 0.8, 0.3})),
//		new Sphere({-4.0, 0.0, -4.0}, 2.0, new Dielectric(1.5)),
//		new Sphere({0.0, -402, -4.0}, 400.0, new Metal({0.8, 0.6, 0.2}, 0.04))
//	};
	Object *world = random_scene();
	int width = 800;
	int height = 400;
	int ns = 100;
	Camera camera{
		{52.0, 8.0, 12.0},
		{0.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
		20,
		double(width) / double(height),
		0.1,
		40.0,
		0.0,
		1.0
	};
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
				col += color(r, world, 0);
			}
			col /= ns;
			canvas.pixels[i][j] = {sqrt(col.x), sqrt(col.y), sqrt(col.z)};
		}
	}
	canvas.setImageFormat(ppm);
	canvas.exportTo("../../../Outputs/1.ppm");
	return 0;
}

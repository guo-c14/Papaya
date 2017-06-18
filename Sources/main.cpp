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
#include <thread>
#include "Vector.h"
#include "Object.h"
#include "Sphere.h"
#include "Ray.h"
#include "Camera.h"
#include "Canvas.h"
#include "Material.h"
#include "AABB.h"
#include "BVHNode.h"

using std::vector;

Pixel color(const Ray &r, const Object *world, int depth) {
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
	vector<Object *> list;
	list.push_back(new Sphere(Vector(0, -4000, 0), 4000, new Diffuse(Vector(0.5, 0.5, 0.5))));
	for (int a = -10; a < 10; a++) {
		for (int b = -10; b < 10; b++) {
			float choose_mat = drand48();
			Vector center(4 * a + 3.6 * drand48(), 0.8, 4 * b + 3.6 * drand48());
			if (distance(center, {16, 0.8, 0}) > 3.6) {
				if (choose_mat < 0.4) {
					list.push_back(new Sphere(center, 0.8, new Diffuse(Vector(drand48() * drand48(), drand48() * drand48(), drand48() * drand48()))));
				}
				else if (choose_mat < 0.8) {
					list.push_back(new MovingSphere(center, center + Vector(0, 2.0 * drand48(), 0), 0.0, 1.0, 0.8, new Diffuse(Vector(drand48() * drand48(), drand48() * drand48(), drand48() * drand48()))));
				}
				else if (choose_mat < 0.88) {
					list.push_back(new Sphere(center, 0.8, new Metal(Vector(0.5 * (1 + drand48()), 0.5 * (1 + drand48()), 0.5 * (1 + drand48())), 0.5 * drand48())));
				}
				else if (choose_mat < 0.96) {
					list.push_back(new MovingSphere(center, center + Vector(0, 2.0 * drand48(), 0), 0.0, 1.0, 0.8, new Metal(Vector(0.5 * (1 + drand48()), 0.5 * (1 + drand48()), 0.5 * (1 + drand48())), 0.5 * drand48())));
				}
				else if (choose_mat < 0.98)  {
					list.push_back(new Sphere(center, 0.8, new Dielectric(1.5)));
				} else {
					list.push_back(new MovingSphere(center, center + Vector(0, 2.0 * drand48(), 0), 0.0, 1.0, 0.8, new Dielectric(1.5)));
				}
			}
		}
	}
	list.push_back(new Sphere(Vector(0, 4, 0), 4.0, new Dielectric(1.5)));
	list.push_back(new Sphere(Vector(-16, 4, 0), 4.0, new Diffuse(Vector(0.4, 0.2, 0.1))));
	list.push_back(new Sphere(Vector(16, 4, 0), 4.0, new Metal(Vector(0.7, 0.6, 0.5), 0.0)));
	return new ObjectList(list);
}

Object **random_scene1(int &i) {
	Object **list = new Object *[500];
	list[i++] = new Sphere(Vector(0, -4000, 0), 4000, new Diffuse(Vector(0.5, 0.5, 0.5)));
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
	return list;
}

void call_from_thread(vector<vector<Pixel>> &pixels, int startRow, int endRow, int width, int height, const Camera &camera, const Object *world) {
	for (int i = startRow; i < endRow; i++) {
		pixels[i - startRow] = vector<Pixel>(width);
		for (int j = 0; j < width; j++) {
			Pixel col;
			for (int k = 0; k < 100; k++) {
				double u = static_cast<double>(j + drand48()) / width;
				double v = 1.0 - static_cast<double>(i + drand48()) / height;
				Ray r(camera.getRay(u, v));
				col += color(r, world, 0);
			}
			col /= 100;
			pixels[i - startRow][j] = {sqrt(col.x), sqrt(col.y), sqrt(col.z)};
		}
	}
}

int main(int argc, const char * argv[]) {
	Vector low_left_corner(-2.0, -1.0, -1.0);
	Vector horizontal(4.0, 0.0, 0.0);
	Vector vertical(0.0, 2.0, 0.0);
	Vector origin(0.0, 0.0, 0.0);
//	Object *world = random_scene();
	int i = 0;
	Object **list = random_scene1(i);
	Object *world = new BVHNode(list, i, 0, 1);
	int width = 800;
	int height = 400;
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
	canvas.pixels = vector<vector<Pixel>>();
	vector<vector<Pixel>> first_part(height*5/16);
	vector<vector<Pixel>> second_part(height*9/16-height*5/16);
	vector<vector<Pixel>> third_part(height*13/16-height*9/16);
	vector<vector<Pixel>> forth_part(height-height*13/16);
	std::thread t0(call_from_thread, std::ref(first_part), 0, height*5/16, width, height, std::ref(camera), world);
	std::thread t1(call_from_thread, std::ref(second_part), height*5/16, height*9/16, width, height, std::ref(camera), world);
	std::thread t2(call_from_thread, std::ref(third_part), height*9/16, height*13/16, width, height, std::ref(camera), world);
	std::thread t3(call_from_thread, std::ref(forth_part), height*13/16, height, width, height, std::ref(camera), world);
	t0.join();
	t1.join();
	t2.join();
	t3.join();
	for (int i = 0; i < height*5/16; i++) {
		canvas.pixels.push_back(first_part[i]);
	}
	for (int i = 0; i < height*9/16 - height*5/16; i++) {
		canvas.pixels.push_back(second_part[i]);
	}
	for (int i = 0; i < height*13/16 - height*9/16; i++) {
		canvas.pixels.push_back(third_part[i]);
	}
	for (int i = 0; i < height - height*13/16; i++) {
		canvas.pixels.push_back(forth_part[i]);
	}
//	int ns = 100;
//	canvas.pixels = vector<vector<Pixel>>(height);
//	for (int i = 0; i < height; i++) {
//		canvas.pixels[i] = vector<Pixel>(width);
//		for (int j = 0; j < width; j++) {
//			Pixel col;
//			for (int k = 0; k < ns; k++) {
//				double u = static_cast<double>(j + drand48()) / width;
//				double v = 1.0 - static_cast<double>(i + drand48()) / height;
//				Ray r(camera.getRay(u, v));
//				col += color(r, world, 0);
//			}
//			col /= ns;
//			canvas.pixels[i][j] = {sqrt(col.x), sqrt(col.y), sqrt(col.z)};
//		}
//	}
	canvas.setImageFormat(ppm);
	canvas.exportTo("../../../Outputs/1.ppm");
	return 0;
}

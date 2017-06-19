//
//  main.cpp
//  Papaya
//
//  Created by Guo Chen on 6/17/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include <iostream>
#include <vector>
#include <thread>
#include "Canvas.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include "Material.hpp"
#include "Texture.hpp"
#include "BVH.hpp"
#include "Sphere.hpp"
#include "Utility.hpp"

using std::vector;

Vec3D color(const Ray &r, const Object *world, int depth) {
	HitRecord rec;
	if (world->hit(r, 0.001, 0x1.fffffep+127f, rec)) {
		Vec3D attenutation;
		Ray scattered;
		if (depth < 50 && rec.material->scatter(r, rec, attenutation, scattered)) {
			return attenutation * color(scattered, world, depth + 1);
		} else {
			return 0;
		}
	}
	else {
		double t = 0.5 * r.direction.y + 0.5;
		return (1.0 - t) * Vec3D(1.0, 1.0, 1.0) + t * Vec3D(0.5, 0.7, 1.0);
	}
}

Object **random_scene(int &i) {
	Texture *texture = new CheckerTexture(new ConstantTexture({1.0, 1.0, 1.0}), new ConstantTexture({0.0118, 0.6627, 0.9725}));
	Object **list = new Object *[500];
	list[i++] = new Sphere(Vec3D(0, -4000, 0), 4000, new Diffuse(texture));
	for (int a = -10; a < 10; a++) {
		for (int b = -10; b < 10; b++) {
			float choose_mat = drand();
			Vec3D center(4 * a + 3.6 * drand(), 0.8, 4 * b + 3.6 * drand());
			if (distance(center, {16, 0.8, 0}) > 3.6) {
				if (choose_mat < 0.4) {
					list[i++] = new Sphere(center, 0.8, new Diffuse(new ConstantTexture(Vec3D(drand() * drand(), drand() * drand(), drand() * drand()))));
				}
				else if (choose_mat < 0.8) {
					list[i++] = new MovingSphere(center, center + Vec3D(0, 2.0 * drand(), 0), 0.0, 1.0, 0.8, new Diffuse(new ConstantTexture(Vec3D(drand() * drand(), drand() * drand(), drand() * drand()))));
//					list[i++] = new Sphere(center, 0.8, new Diffuse(new ConstantTexture(Vec3D(drand() * drand(), drand() * drand(), drand() * drand()))));
				}
				else if (choose_mat < 0.88) {
					list[i++] = new Sphere(center, 0.8, new Metal(Vec3D(0.5 * (1 + drand()), 0.5 * (1 + drand()), 0.5 * (1 + drand())), 0.5 * drand()));
				}
				else if (choose_mat < 0.96) {
					list[i++] = new MovingSphere(center, center + Vec3D(0, 2.0 * drand(), 0), 0.0, 1.0, 0.8, new Metal(Vec3D(0.5 * (1 + drand()), 0.5 * (1 + drand()), 0.5 * (1 + drand())), 0.5 * drand()));
//					list[i++] = new Sphere(center, 0.8, new Metal(Vec3D(0.5 * (1 + drand()), 0.5 * (1 + drand()), 0.5 * (1 + drand())), 0.5 * drand()));
				}
				else if (choose_mat < 0.98)  {
					list[i++] = new Sphere(center, 0.8, new Dielectric(1.5));
				} else {
					list[i++] = new MovingSphere(center, center + Vec3D(0, 2.0 * drand(), 0), 0.0, 1.0, 0.8, new Dielectric(1.5));
//					list[i++] = new Sphere(center, 0.8, new Dielectric(1.5));
				}
			}
		}
	}
	list[i++] = new Sphere(Vec3D(0, 4, 0), 4.0, new Dielectric(1.5));
	list[i++] = new Sphere(Vec3D(-16, 4, 0), 4.0, new Diffuse(new ConstantTexture(Vec3D(0.4, 0.2, 0.1))));
	list[i++] = new Sphere(Vec3D(16, 4, 0), 4.0, new Metal(Vec3D(0.7, 0.6, 0.5), 0.0));
	return list;
}

void call_from_thread(vector<vector<Color>> &pixels, int startRow, int endRow, int width, int height, const Camera &camera, const Object *world) {
	for (int i = startRow; i < endRow; i++) {
		pixels[i - startRow] = vector<Color>(width);
		for (int j = 0; j < width; j++) {
			Vec3D col;
			for (int k = 0; k < 100; k++) {
				double u = static_cast<double>(j + drand()) / width;
				double v = 1.0 - static_cast<double>(i + drand()) / height;
				Ray r(camera.emitRay(u, v));
				col += color(r, world, 0);
			}
			col /= 100;
			pixels[i - startRow][j] = Vec3D{sqrt(col.x), sqrt(col.y), sqrt(col.z)};
		}
	}
}

int main(int argc, const char *argv[]) {
	int i = 0;
	Object **list = random_scene(i);
	Object *world = new BVH(list, i, 0, 1);
	int width = 800;
	int height = 400;
	Camera camera{
		{52.0, 8.0, 12.0},
		{0.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
		20,
		double(width) / double(height),
		0.4,
		distance({52.0, 8.0, 12.0}, {0.0, 0.0, 0.0}),
		0.0,
		1.0
	};
	Canvas canvas;
	canvas.pixels = vector<vector<Color>>();
	vector<vector<Color>> first_part(height*5/16);
	vector<vector<Color>> second_part(height*9/16-height*5/16);
	vector<vector<Color>> third_part(height*13/16-height*9/16);
	vector<vector<Color>> forth_part(height-height*13/16);
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
	canvas.setImageFormat(ppm);
	canvas.exportImage("../../../Outputs/1.ppm");
	return 0;
}

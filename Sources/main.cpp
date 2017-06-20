//
//  main.cpp
//  Papaya
//
//  Created by Guo Chen on 6/17/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include <iostream>

#include "Canvas.hpp"
#include "Camera.hpp"
#include "Material.hpp"
#include "Texture.hpp"
#include "BVH.hpp"
#include "Sphere.hpp"
#include "Utility.hpp"

Object **random_scene(int &i) {
	Object **list = new Object *[500];
	list[i++] = new Sphere(Vec3D(0, -4000, 0), 4000, new Metal(1, 0.02));
	for (int a = -10; a < 10; a++) {
		for (int b = -10; b < 10; b++) {
			float choose_mat = drand();
			Vec3D center(4 * a + 3.6 * drand(), 0.8, 4 * b + 3.6 * drand());
			if (distance(center, {16, 0.8, 0}) > 3.6) {
				if (choose_mat < 0.4) {
					list[i++] = new Sphere {
						center,
						0.8,
						new Diffuse {
							{drand() * drand(), drand() * drand(), drand() * drand()}
						}
					};
				}
				else if (choose_mat < 0.88) {
					list[i++] = new Sphere {
						center,
						0.8,
						new Metal {
							Vec3D(0.5 * (1 + drand()), 0.5 * (1 + drand()), 0.5 * (1 + drand())),
							0.5 * drand()
						}
					};
				}
				else {
					list[i++] = new Sphere(center, 0.8, new Dielectric(1.5));
				}
			}
		}
	}
	list[i++] = new Sphere(Vec3D(0, 4, 0), 4.0, new Dielectric(1.5));
	list[i++] = new Sphere(Vec3D(-16, 4, 0), 4.0, new Diffuse(new ConstantTexture(Vec3D(0.4, 0.2, 0.1))));
	list[i++] = new Sphere(Vec3D(16, 4, 0), 4.0, new Metal(Vec3D(0.7, 0.6, 0.5), 0.0));
	return list;
}

int main(int argc, const char *argv[]) {
	int n = 0;
	Object **list = random_scene(n);
	Object *scene = new BVH(list, n, 0, 1);
	int width = 800;
	int height = 450;
	Vec3D lookfrom(52, 8, 12);
	Vec3D lookat(0);
	Vec3D vup(0, 1, 0);
	double vfov = 20;
	double aspect = static_cast<double>(width) / static_cast<double>(height);
	double aperture = 0;
	double focus_dist = distance(lookfrom, lookat);
	double exposure_start_time = 0;
	double exposure_stop_time = 1;
	Camera camera{
		lookfrom,
		lookat,
		vup,
		vfov,
		aspect,
		aperture,
		focus_dist,
		exposure_start_time,
		exposure_stop_time
	};
	Canvas canvas(width, height, 128, 64);
	canvas.render(camera, scene, 4);
	canvas.exportImage("../../../Outputs/1.ppm", ppm);
	return 0;
}

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
#include "Cube.hpp"
#include "Light.hpp"
#include "Utility.hpp"

#include <vector>

using std::vector;

Object **cornell_box(Camera &camera, int &i, int &width, int &height) {
	i = 0;
	width = 500;
	height = 500;
	Vec3D lookfrom(278, 278, -800);
	Vec3D lookat(278, 278, 0);
	Vec3D vup(0, 1, 0);
	double vfov = 40;
	double aspect = static_cast<double>(width) / static_cast<double>(height);
	double aperture = 0;
	double focus_dist = 10;
	double exposure_start_time = 0;
	double exposure_stop_time = 1;
	camera = {
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
	Object **list = new Object *[10];
	Material *red = new Diffuse({0.65, 0.05, 0.05});
	Material *white = new Diffuse({0.73, 0.73, 0.73});
	Material *green = new Diffuse({0.12, 0.45, 0.15});
	Material *light = new DiffuseLight(1);
	list[i++] = new FlipNormal(new RectangleYZ(0, 555, 0, 555, 555, red));
	list[i++] = new RectangleYZ(0, 555, 0, 555, 0, green);
	list[i++] = new RectangleXZ(200, 355, 200, 355, 554, light);
	list[i++] = new FlipNormal(new RectangleXZ(0, 555, 0, 555, 555, white));
	list[i++] = new RectangleXZ(0, 555, 0, 555, 0, white);
	list[i++] = new FlipNormal(new RectangleXY(0, 555, 0, 555, 555, white));
	list[i++] = new Translate(new Sphere(80, 80, new Dielectric(1.55, {0.12, 0.45, 0.15})), {300, 0, 65});
	list[i++] = new Translate(new RotateY(new Cube(0, {165, 330, 165}, white), -15), {125, 0, 295});
	return list;
}

Object **simple_lights(Camera &camera, int &i, int &width, int &height) {
	i = 0;
	width = 800;
	height = 450;
	Vec3D lookfrom(52, 8, 12);
	Vec3D lookat(0);
	Vec3D vup(0, 1, 0);
	double vfov = 20;
	double aspect = static_cast<double>(width) / static_cast<double>(height);
	double aperture = 0;
	double focus_dist = distance(lookfrom, lookat);
	double exposure_start_time = 0;
	double exposure_stop_time = 1;
	camera = {
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
	Texture *texture0 = new ImageTexture("../../../Textures/Floor.ppm", ppm, 600, 600);
	Texture *texture1 = new ImageTexture("../../../Textures/Marble.ppm", ppm, 1024, 1024);
	Object **list = new Object *[10];
	list[i++] = new RectangleXZ(-100, 100, 0, 200, 50, new DiffuseLight(0.8));
	list[i++] = new Sphere(Vec3D(0, -4000, 0), 4000, new Diffuse(texture0));
	list[i++] = new Sphere(Vec3D(0, 4, 0), 4.0, new Dielectric(1.5));
	list[i++] = new Sphere(Vec3D(-16, 4, 0), 4.0, new Diffuse(texture1));
	list[i++] = new Sphere(Vec3D(16, 4, 0), 4.0, new Metal(texture1, 0.1));
	return list;
}

Object **random_scene(Camera &camera, int &i, int &width, int &height) {
	i = 0;
	width = 800;
	height = 450;
	Vec3D lookfrom(52, 8, 12);
	Vec3D lookat(0);
	Vec3D vup(0, 1, 0);
	double vfov = 20;
	double aspect = static_cast<double>(width) / static_cast<double>(height);
	double aperture = 0;
	double focus_dist = distance(lookfrom, lookat);
	double exposure_start_time = 0;
	double exposure_stop_time = 1;
	camera = {
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
	Object **list = new Object *[500];
	list[i++] = new Sphere(Vec3D(0, -4000, 0), 4000, new DiffuseLight(0.8));
//	list[i++] = new Sphere(Vec3D(0, -4000, 0), 4000, new Diffuse(new ImageTexture("../../../Textures/Floor.ppm", ppm, 600, 600)));
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
	list[i++] = new Sphere(Vec3D(-16, 4, 0), 4.0, new Diffuse(new ImageTexture("../../../Textures/Marble.ppm", ppm, 1024, 1024)));
	list[i++] = new Sphere(Vec3D(16, 4, 0), 4.0, new Metal(new ImageTexture("../../../Textures/Marble.ppm", ppm, 1024, 1024), 0.8));
	return list;
}

Object **scene_1(Camera &camera, int &i, int &width, int &height) {
	i = 0;
	width = 1200;
	height = 720;
	Vec3D lookfrom(-40, 160, 200);
	Vec3D lookat(0, 0, 0);
	Vec3D vup(0, 1, 0);
	double vfov = 40;
	double aspect = static_cast<double>(width) / static_cast<double>(height);
	double aperture = 0;
	double focus_dist = distance(lookfrom, lookat);
	double exposure_start_time = 0;
	double exposure_stop_time = 1;
	camera = {
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
	Object **list = new Object *[10];
	Texture *texture0 = new ImageTexture("../Textures/Floor.ppm", ppm, 600, 600);
	Texture *texture1 = new ImageTexture("../Textures/EarthLowRes.ppm", ppm, 1024, 512);
	Material *light = new DiffuseLight(3.6);
//	list[i++] = new RectangleXZ(-140, 340, -540, -60, 240, light);
	list[i++] = new Sphere({100, 260, -300}, 140, light);
	list[i++] = new Sphere({-25, 10, 10}, 10, new GeneralMaterial({0, 0.7, 0.3}, {1, 1, 1}, 0.01, {0, 1, 1}, 1.55));
	list[i++] = new Sphere({0, 10, 5}, 10, new GeneralMaterial({0, 0.5, 0.5}, {1, 1, 1}, 0.01, {1, 0, 1}, 1.5));
	list[i++] = new Sphere({25, 10, 0}, 10, new GeneralMaterial({0, 0.3, 0.7}, {1, 1, 1}, 0.01, {1, 1, 0}, 1.45));
	list[i++] = new Sphere({75, 20, -70}, 20, new GeneralMaterial({0, 0.1, 0.9}, {1, 1, 1}, 0.01, {0.5, 0.5, 1}, 1.4));
	list[i++] = new Sphere({-25, 25, -55}, 25, new GeneralMaterial({0.7, 0.05, 0.25}, texture1, 0.02, {0.4, 0.4, 0.8}, 1.5));
	list[i++] = new RectangleXZ(-320, 320, -320, 320, 0, new GeneralMaterial({0.96, 0.04, 0}, texture0, 0.02, 0, 0));
	return list;
}

int main(int argc, const char *argv[]) {
	Camera camera;
	int n, width, height;
	Object **list = scene_1(camera, n, width, height);
	Object *scene = new BVH(list, n, 0, 1);
	Canvas canvas(width, height, 4096, 64);
//	Canvas canvas(width, height);
	canvas.render(camera, scene, 4);
	canvas.exportImage("../Outputs/1.ppm", ppm);
	return 0;
}

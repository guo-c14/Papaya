//
//  Scene.h
//  Papaya
//
//  Created by Guo Chen on 6/23/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include "config.hpp"
#include "Utility.hpp"
#include "Camera.hpp"
#include "Material.hpp"
#include "Texture.hpp"
#include "BVH.hpp"
#include "Light.hpp"
#include "Sphere.hpp"
#include "Cube.hpp"
#include "BezierModel.hpp"
#include "Triangle.hpp"
#include "ObjParser.hpp"

Object **dragon_cornell(Camera &camera, int &i, int &width, int &height) {
	i = 0;
	width = 800;
	height = 800;
	Vec3D lookfrom(300, 300, 850);
	Vec3D lookat(300, 300, -300);
	Vec3D vup(0, 1, 0);
	double vfov = 40;
	double aspect = static_cast<double>(width) / static_cast<double>(height);
	double aperture = 40;
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
	Material *red = new Diffuse({0.65, 0.05, 0.05});
	Material *white = new Diffuse({0.73, 0.73, 0.73});
	Material *green = new Diffuse({0.12, 0.45, 0.15});
	Material *light = new DiffuseLight(6);
	Material *dragon_mtl = new GeneralMaterial({0.1, 0.9, 0}, {0.8, 0.8, 0.4}, 0.1, 0, 0);
	Material *dragon_mtl1 = new GeneralMaterial({0, 0.2, 0.8}, 1, 0.01, {0.6, 0.4, 0.8}, 1.5);
	Object **list = new Object *[9];
	list[i++] = new FlipNormal(new RectangleYZ(0, 600, -600, 0, 600, red));
	list[i++] = new RectangleYZ(0, 600, -600, 0, 0, green);
	list[i++] = new RectangleXZ(220, 380, -380, -220, 599, light);
	list[i++] = new FlipNormal(new RectangleXZ(0, 600, -600, 0, 600, white));
	list[i++] = new RectangleXZ(0, 600, -600, 0, 0, white);
	list[i++] = new RectangleXY(0, 600, 0, 600, -600, white);
	ObjParser parser;
	BVH *dragon0, *dragon1, *dragon2;
	dragon0 = parser.read(MODELS_DIRECTORY + "dragon.obj", dragon_mtl, 100);
	dragon1 = parser.read(MODELS_DIRECTORY + "dragon.obj", dragon_mtl, 100);
	dragon2 = parser.read(MODELS_DIRECTORY + "dragon.obj", dragon_mtl1, 100);
	list[i++] = new Translate(dragon0, {450, 70, -150});
	list[i++] = new Translate(dragon1, {150, 70, -450});
	list[i++] = new Translate(dragon2, {300, 70, -300});
	return list;
}

Object **bezier_curve(Camera &camera, int &i, int &width, int &height) {
	i = 0;
	width = 800;
	height = 600;
	Vec3D lookfrom(0, 90, 700);
	Vec3D lookat(0, 0, 400);
	Vec3D vup(0, 1, 0);
	double vfov = 40;
	double aspect = static_cast<double>(width) / static_cast<double>(height);
	double aperture = 4;
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
	Object **list = new Object *[20];
	Material *china = new GeneralMaterial({1, 0, 0}, new ImageTexture(TEXTURES_DIRECTORY + "China.ppm", ppm, 560, 444), 0.4, {0.5, 0.5, 1}, 1.4);
	vector<Vec3D> points{{10, 0, 0}, {43, 10, 0}, {43, 50, 0}, {0, 50, 0}, {26.7, 92, 0}};
	list[i++] = new Translate {
		new BezierModel{
			BezierCurve(points),
			china
		},
		{-50, 0, 400}
	};
	ObjParser parser;
	BVH *dragon;
	dragon = parser.read(MODELS_DIRECTORY + "dragon.obj", new GeneralMaterial({0.1, 0.9, 0}, {0.8, 0.8, 0.4}, 0.1, 0, 0), 40);
	list[i++] = new Translate(dragon, {30, 28, 500});
	Texture *marble_texture = new ImageTexture(TEXTURES_DIRECTORY + "Marble.ppm", ppm, 1024, 1024);
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			list[i++] = new RectangleXZ(-1000 + k * 400, -600 + k * 400, -1000 + j * 400, -600 + j * 400, 0, new GeneralMaterial({0.2, 0.8, 0}, marble_texture, 0.01, 0, 0));
		}
	}
	return list;
}

Object **bezier_cornell(Camera &camera, int &i, int &width, int &height) {
	i = 0;
	width = 800;
	height = 800;
	Vec3D lookfrom(300, 300, 850);
	Vec3D lookat(300, 300, -300);
	Vec3D vup(0, 1, 0);
	double vfov = 40;
	double aspect = static_cast<double>(width) / static_cast<double>(height);
	double aperture = 30;
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
	Material *red = new Diffuse({0.65, 0.05, 0.05});
	Material *white = new Diffuse({0.73, 0.73, 0.73});
	Material *green = new Diffuse({0.12, 0.45, 0.15});
	Material *light = new DiffuseLight(12);
	Material *dragon_mtl = new GeneralMaterial({0.1, 0.9, 0}, {0.8, 0.8, 0.4}, 0.1, 0, 0);
	Object **list = new Object *[9];
	list[i++] = new FlipNormal(new RectangleYZ(0, 600, -600, 0, 600, red));
	list[i++] = new RectangleYZ(0, 600, -600, 0, 0, green);
	list[i++] = new RectangleXZ(220, 380, -380, -220, 599, light);
	list[i++] = new FlipNormal(new RectangleXZ(0, 600, -600, 0, 600, white));
	list[i++] = new RectangleXZ(0, 600, -600, 0, 0, white);
	list[i++] = new RectangleXY(0, 600, 0, 600, -600, white);
	ObjParser parser;
	BVH *dragon1, *dragon2;
	dragon1 = parser.read(MODELS_DIRECTORY + "dragon.obj", dragon_mtl, 110);
	dragon2 = parser.read(MODELS_DIRECTORY + "dragon.obj", dragon_mtl, 110);
	list[i++] = new Translate(dragon1, {440, 77, -140});
	Material *china = new GeneralMaterial({0.8, 0.2, 0}, new ImageTexture(TEXTURES_DIRECTORY + "China.ppm", ppm, 560, 444), 0.02, {0.5, 0.5, 1}, 1.4);
	vector<Vec3D> points{{35, 0, 0}, {131.25, 43.75, 0}, {131.25, 131.25, 0}, {0, 131.25, 0}, {52.5, 262.5, 0}};
	list[i++] = new Translate {
		new BezierModel{
			BezierCurve(points),
			china
		},
		{300, 0, -300}
	};
	list[i++] = new Translate(dragon2, {140, 77, -440});
	return list;
}

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
	Material *light = new DiffuseLight(6);
	list[i++] = new FlipNormal(new RectangleYZ(0, 555, 0, 555, 555, red));
	list[i++] = new RectangleYZ(0, 555, 0, 555, 0, green);
	list[i++] = new Triangle({177, 554, 200}, {277, 554, 373}, {377, 554, 200}, light);
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
	Texture *texture0 = new ImageTexture(TEXTURES_DIRECTORY + "Floor.ppm", ppm, 600, 600);
	Texture *texture1 = new ImageTexture(TEXTURES_DIRECTORY + "Marble.ppm", ppm, 1024, 1024);
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
	list[i++] = new Sphere(Vec3D(-16, 4, 0), 4.0, new Diffuse(new ImageTexture(TEXTURES_DIRECTORY + "Marble.ppm", ppm, 1024, 1024)));
	list[i++] = new Sphere(Vec3D(16, 4, 0), 4.0, new Metal(new ImageTexture(TEXTURES_DIRECTORY + "Marble.ppm", ppm, 1024, 1024), 0.8));
	return list;
}

#endif /* Scene_hpp */

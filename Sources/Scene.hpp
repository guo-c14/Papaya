//
//  Scene.h
//  Papaya
//
//  Created by Guo Chen on 6/23/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include "Canvas.hpp"
#include "Camera.hpp"
#include "Material.hpp"
#include "Texture.hpp"
#include "BVH.hpp"
#include "Sphere.hpp"
#include "Cube.hpp"
#include "Light.hpp"
#include "Utility.hpp"
#include "BezierModel.hpp"
#include "Triangle.hpp"
#include "Circle.hpp"
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
#ifdef XCODE
	dragon0 = parser.read("../../../Models/dragon.obj", dragon_mtl, 100);
	dragon1 = parser.read("../../../Models/dragon.obj", dragon_mtl, 100);
	dragon2 = parser.read("../../../Models/dragon.obj", dragon_mtl1, 100);
#else
	dragon0 = parser.read("../Models/dragon.obj", dragon_mtl, 100);
	dragon1 = parser.read("../Models/dragon.obj", dragon_mtl, 100);
	dragon2 = parser.read("../Models/dragon.obj", dragon_mtl1, 100);
#endif
	list[i++] = new Translate(dragon0, {450, 70, -150});
	list[i++] = new Translate(dragon1, {150, 70, -450});
	list[i++] = new Translate(dragon2, {300, 70, -300});
	return list;
}

Object **bezier_curve(Camera &camera, int &i, int &width, int &height) {
	i = 0;
	width = 800;
	height = 600;
	Vec3D lookfrom(40, 210, 680);
	Vec3D lookat(0, 0, 400);
	Vec3D vup(0, 1, 0);
	double vfov = 40;
	double aspect = static_cast<double>(width) / static_cast<double>(height);
	double aperture = 6;
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
#ifdef XCODE
	Material *china = new GeneralMaterial({0.3, 0.7, 0}, new ImageTexture("../../../Textures/China.ppm", ppm, 560, 444), 0.01, {0.5, 0.5, 1}, 1.4);
#else
	Material *china = new GeneralMaterial({0.3, 0.7, 0}, new ImageTexture("../Textures/China.ppm", ppm, 560, 444), 0.01, {0.5, 0.5, 1}, 1.4);
#endif
	vector<Vec3D> points{{6, 0, 0}, {26, 6, 0}, {26, 30, 0}, {0, 30, 0}, {16, 55, 0}};
	list[i++] = new Translate {
		new BezierModel{
			BezierCurve(points),
			china
		},
		{0, 0, 400}
	};
	ObjParser parser;
	BVH *dragon;
#ifdef XCODE
	dragon = parser.read("../../../Models/dragon.obj", new GeneralMaterial({0.1, 0.9, 0}, {0.8, 0.8, 0.4}, 0.1, 0, 0), 25);
#else
	dragon = parser.read("../Models/dragon.obj", new GeneralMaterial({0.1, 0.9, 0}, {0.8, 0.8, 0.4}, 0.1, 0, 0), 25);
#endif
	list[i++] = new Translate(dragon, {60, 17.5, 500});
#ifdef XCODE
	Texture *marble_texture = new ImageTexture("../../../Textures/Marble.ppm", ppm, 1024, 1024);
#else
	Texture *marble_texture = new ImageTexture("../Textures/Marble.ppm", ppm, 1024, 1024);
#endif
	for (int j = 0; j < 4; j++) {
		for (int k = 0; k < 4; k++) {
			list[i++] = new RectangleXZ(-600 + k * 300, -300 + k * 300, -600 + j * 300, -300 + j * 300, 0, new GeneralMaterial({0.2, 0.8, 0}, marble_texture, 0.01, 0, 0));
		}
	}
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
	Material *light = new DiffuseLight(4);
	list[i++] = new FlipNormal(new RectangleYZ(0, 555, 0, 555, 555, red));
	list[i++] = new RectangleYZ(0, 555, 0, 555, 0, green);
	//	list[i++] = new RectangleXZ(200, 355, 200, 355, 554, light);
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
	width = 800;
	height = 450;
	Vec3D lookfrom(-85, 160, 165);
	Vec3D lookat(0, 0, 0);
	Vec3D vup(0, 1, 0);
	double vfov = 45;
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
	Object **list = new Object *[20];
#ifdef XCODE
	Texture *texture0 = new ImageTexture("../../../Textures/Floor.ppm", ppm, 600, 600);
	Texture *texture1 = new ImageTexture("../../../Textures/EarthLowRes.ppm", ppm, 1024, 512);
	Texture *texture2 = new ImageTexture("../../../Textures/BlueGlass.ppm", ppm, 600, 417);
	Texture *texture3 = new ImageTexture("../../../Textures/Marble.ppm", ppm, 1024, 1024);
#else
	Texture *texture0 = new ImageTexture("../Textures/Floor.ppm", ppm, 600, 600);
	Texture *texture1 = new ImageTexture("../Textures/EarthLowRes.ppm", ppm, 1024, 512);
	Texture *texture2 = new ImageTexture("../Textures/BlueGlass.ppm", ppm, 600, 417);
	Texture *texture3 = new ImageTexture("../Textures/Marble.ppm", ppm, 1024, 1024);
#endif
	Material *light = new DiffuseLight({3.6, 3.6, 3.6});
	list[i++] = new Sphere({125, 300, -295}, 150, light);
	list[i++] = new Sphere({-15, 10, 20}, 10, new GeneralMaterial({0, 0.7, 0.3}, {1, 1, 1}, 0.01, {0, 1, 1}, 1.55));
	list[i++] = new Sphere({10, 10, 15}, 10, new GeneralMaterial({0, 0.5, 0.5}, {1, 1, 1}, 0.01, {1, 0, 1}, 1.5));
	list[i++] = new Sphere({35, 10, 10}, 10, new GeneralMaterial({0, 0.3, 0.7}, {1, 1, 1}, 0.01, {1, 1, 0}, 1.45));
	//	list[i++] = new Sphere({75, 20, -70}, 20, new GeneralMaterial({0, 0.1, 0.9}, {1, 1, 1}, 0.01, {0.5, 0.5, 1}, 1.4));
	vector<Vec3D> points1{{14, 0, 0}, {24, 8, 0}, {24, 30, 0}, {12, 24, 0}, {8, 66, 0}};
	list[i++] = new Translate {
		new BezierModel{
			BezierCurve(points1),
			new GeneralMaterial({0, 0.2, 0.8}, {1, 1, 1}, 0.01, {0.5, 0.5, 1}, 1.4)
		},
		{55, 0, -50}
	};
	list[i++] = new Circle({55, 0, -50}, {0, -1, 0}, 14, new GeneralMaterial({0, 0.2, 0.8}, {1, 1, 1}, 0.01, {1.0, 0.5, 0.5}, 1.4));
	list[i++] = new Circle({55, 66, -50}, {0, 1, 0}, 8, new GeneralMaterial({0, 0.2, 0.8}, {1, 1, 1}, 0.01, {1.0, 0.5, 0.5}, 1.4));
	list[i++] = new Sphere({-15, 25, -45}, 25, new GeneralMaterial({0, 0.1, 0.9}, {1, 1, 1}, 0.01, {0.8, 0.3, 0.7}, 1.4));
	list[i++] = new RectangleXZ(-450, 450, -450, 450, 0, new GeneralMaterial({0.94, 0.06, 0}, texture0, 0.02, 0, 0));
	ObjParser parser;
#ifdef XCODE
	list[i++] = new Translate {
		parser.read("../../../Models/dragon.obj", new GeneralMaterial({0.1, 0.2, 0.7}, {1, 1, 1}, 0.01, {0.4, 0.7, 1}, 1.4), 30),
		{-50, 21, 0}
	};
#else
	list[i++] = new Translate {
		parser.read("../Models/dragon.obj", new GeneralMaterial({0.1, 0.2, 0.7}, {1, 1, 1}, 0.01, {0.4, 0.7, 1}, 1.4), 30),
		{-50, 21, 0}
	};
#endif
	return list;
}

Object **cub_and_triangles(Camera &camera, int &i, int &width, int &height) {
	i = 0;
	width = 800;
	height = 450;
	Vec3D lookfrom(-85, 170, 165);
	Vec3D lookat(0, 0, 0);
	Vec3D vup(0, 1, 0);
	double vfov = 45;
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
	Object **list = new Object *[20];
	Material *light = new DiffuseLight({3.6, 3.6, 3.6});
	list[i++] = new Sphere({125, 300, -295}, 150, light);
	list[i++] = new Cube({-50, 1, -50}, {-11, 41, -11}, new GeneralMaterial({0, 0, 1}, {1, 1, 1}, 0.01, {0.5, 0.5, 1}, 1.4));
	Vec3D v0(1, 1, 1);
	Vec3D v1(41, 1, 1);
	Vec3D v2(1, 41, 1);
	Vec3D v3(41, 41, 1);
	Vec3D v4(1, 1, 41);
	Vec3D v5(41, 1, 41), v6(1, 41, 41), v7(41, 41, 41);
	Triangle *t = new Triangle(v0, v1, v2, new GeneralMaterial({0, 0, 1}, {1, 1, 1}, 0.01, {0.5, 0.5, 1}, 1.4));;
	t->normal = {0, 0, -1};
	list[i++] = t;
	t = new Triangle(v1, v2, v3, new GeneralMaterial({0, 0, 1}, {1, 1, 1}, 0.01, {0.5, 0.5, 1}, 1.4));;
	t->normal = {0, 0, -1};
	list[i++] = t;
	t = new Triangle(v0, v1, v4, new GeneralMaterial({0, 0, 1}, {1, 1, 1}, 0.01, {0.5, 0.5, 1}, 1.4));;
	t->normal = {0, -1, 0};
	list[i++] = t;
	t = new Triangle(v1, v4, v5, new GeneralMaterial({0, 0, 1}, {1, 1, 1}, 0.01, {0.5, 0.5, 1}, 1.4));;
	t->normal = {0, -1, 0};
	list[i++] = t;
	t = new Triangle(v1, v3, v5, new GeneralMaterial({0, 0, 1}, {1, 1, 1}, 0.01, {0.5, 0.5, 1}, 1.4));;
	t->normal = {1, 0, 0};
	list[i++] = t;
	t = new Triangle(v3, v7, v5, new GeneralMaterial({0, 0, 1}, {1, 1, 1}, 0.01, {0.5, 0.5, 1}, 1.4));;
	t->normal = {1, 0, 0};
	list[i++] = t;
	t = new Triangle(v0, v4, v2, new GeneralMaterial({0, 0, 1}, {1, 1, 1}, 0.01, {0.5, 0.5, 1}, 1.4));;
	t->normal = {-1, 0, 0};
	list[i++] = t;
	t = new Triangle(v2, v4, v6, new GeneralMaterial({0, 0, 1}, {1, 1, 1}, 0.01, {0.5, 0.5, 1}, 1.4));;
	t->normal = {-1, 0, 0};
	list[i++] = t;
	t = new Triangle(v6, v4, v5, new GeneralMaterial({0, 0, 1}, {1, 1, 1}, 0.01, {0.5, 0.5, 1}, 1.4));;
	t->normal = {0, 0, 1};
	list[i++] = t;
	t = new Triangle(v6, v7, v5, new GeneralMaterial({0, 0, 1}, {1, 1, 1}, 0.01, {0.5, 0.5, 1}, 1.4));;
	t->normal = {0, 0, 1};
	list[i++] = t;
	t = new Triangle(v2, v3, v6, new GeneralMaterial({0, 0, 1}, {1, 1, 1}, 0.01, {0.5, 0.5, 1}, 1.4));;
	t->normal = {0, 1, 0};
	list[i++] = t;
	t = new Triangle(v7, v3, v6, new GeneralMaterial({0, 0, 1}, {1, 1, 1}, 0.01, {0.5, 0.5, 1}, 1.4));;
	t->normal = {0, 1, 0};
	list[i++] = t;
#ifdef XCODE
	Texture *texture0 = new ImageTexture("../../../Textures/Floor.ppm", ppm, 600, 600);
#else
	Texture *texture0 = new ImageTexture("../Textures/Floor.ppm", ppm, 600, 600);
#endif
	list[i++] = new RectangleXZ(-450, 450, -450, 450, 0, new GeneralMaterial({0.96, 0.04, 0}, texture0, 0.02, 0, 0));
	return list;
}

#endif /* Scene_hpp */

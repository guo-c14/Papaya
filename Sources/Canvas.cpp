//
//  Canvas.cpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include <thread>
#include "Canvas.hpp"
#include "Material.hpp"

using std::thread;

Canvas::Canvas(int width, int height, int samples_per_pixel, int iteration_depth):
width(width), height(height), samples_per_pixel(samples_per_pixel),
iteration_depth(iteration_depth) {
	pixels = vector<vector<Vec3D>>(height);
	for (int i = 0; i < height; i++) {
		pixels[i] = vector<Vec3D>(width);
	}
#ifdef XCODE
	texture = new ImageTexture("../../../Textures/Room.ppm", ppm, 2048, 1024);
//	texture = new ImageTexture("../../../Textures/Home.ppm", ppm, 4000, 2000);
#else
	//	texture = new ImageTexture("../Textures/Room.ppm", ppm, 2048, 1024);
//	texture = new ImageTexture("../Textures/Home.ppm", ppm, 4000, 2000);
#endif
}

Vec3D Canvas::computeColor(const Ray &ray, const Object *scene, int depth) {
	HitRecord record;
	if (scene->hit(ray, 0.0001, MAX_DOUBLE, record)) {
		Ray scattered;
		Vec3D attenutation;
		Vec3D emitted = record.material->emitRay();
		if (depth < iteration_depth && record.material->scatter(ray, record, attenutation, scattered)) {
			return emitted + attenutation * computeColor(scattered, scene, depth + 1);
		} else {
			return emitted;
		}
	}
	else {
//		return 0;
		return texture->value(0.5 - 0.5 * ray.direction.x, 0.5 * ray.direction.y + 0.5, 0);
	}
}

void Canvas::render(const Camera &camera, Object *scene, int threads_num) {
	this->camera = camera;
	this->scene = scene;
	if (threads_num < 1) {
		threads_num = 1;
	} else if (threads_num > 16) {
		threads_num = 16;
	}
	thread threads[threads_num];
	int divide = height / threads_num;
	for (int i = 0; i < threads_num - 1; i++) {
		threads[i] = thread(&Canvas::callFromThread, this, i * divide,
			(i + 1) * divide);
	}
	threads[threads_num - 1] = thread(&Canvas::callFromThread, this,
		(threads_num - 1) * divide, height);
	for (int i = 0; i < threads_num; i++) {
		threads[i].join();
	}
}

void Canvas::callFromThread(int start_row, int end_row) {
	for (int i = start_row; i < end_row; i++) {
		for (int j = 0; j < width; j++) {
			Vec3D col;
			for (int k = 0; k < samples_per_pixel; k++) {
				double u = static_cast<double>(j + drand()) / width;
				double v = 1.0 - static_cast<double>(i + drand()) / height;
				Ray ray(camera.emitRay(u, v));
				col += computeColor(ray, scene, 0);
			}
			col /= samples_per_pixel;
			pixels[i][j] = col;
		}
	}
}

void Canvas::exportImage(const string &fileName, ImageFormat format) const {
	ImageIO *imageIO;
	switch (format) {
		case bmp:
			imageIO = new BMPIO;
			break;
		case jpg:
			imageIO = new JPGIO;
			break;
		case png:
			imageIO = new PNGIO;
			break;
		case ppm:
			imageIO = new PPMIO;
			break;
	}
	imageIO->exportImage(pixels, fileName);
}

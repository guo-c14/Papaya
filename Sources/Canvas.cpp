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

Vec3D Canvas::computeColor(const Ray &ray, const Object *scene, int depth) {
	HitRecord record;
	if (scene->hit(ray, 0.001, 0x1.fffffep+127f, record)) {
		Vec3D attenutation;
		Ray scattered;
		if (depth < iteration_depth && record.material->scatter(ray, record, attenutation, scattered)) {
			return attenutation * computeColor(scattered, scene, depth + 1);
		} else {
			return 0;
		}
	}
	else {
		double t = 0.5 * ray.direction.y + 0.5;
		return (1.0 - t) * Vec3D(1.0, 1.0, 1.0) + t * Vec3D(0.5, 0.7, 1.0);
	}
}

Canvas::Canvas(int width, int height, int samples_per_pixel, int iteration_depth):
	width(width), height(height), samples_per_pixel(samples_per_pixel),
	iteration_depth(iteration_depth) {
	pixels = vector<vector<Color>>(height);
	for (int i = 0; i < height; i++) {
		pixels[i] = vector<Color>(width);
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
			pixels[i][j] = Vec3D{sqrt(col.x), sqrt(col.y), sqrt(col.z)};
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

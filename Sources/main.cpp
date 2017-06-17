//
//  main.cpp
//  Papaya
//
//  Created by Guo Chen on 6/17/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include <iostream>
#include <vector>
#include "Vector.h"
#include "Object.h"
#include "Sphere.h"
#include "Ray.h"
#include "Canvas.h"

using std::vector;

Pixel color(const Ray& r, Object *world) {
	HitRecord rec;
	if (world->hit(r, 0.0, 0x1.fffffep+127f, rec)) {
		return 0.5 * rec.normal + 0.5;
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
		new Sphere({0.0, 0.0, -1.0}, 0.5),
		new Sphere({0.0, -100.5, -1.0}, 100.0)
	};
	Object *world = new ObjectList(list);
	int width = 200;
	int height = 100;
	Canvas canvas;
	canvas.pixels = vector<vector<Pixel>>(height);
	for (int i = 0; i < height; i++) {
		canvas.pixels[i] = vector<Pixel>(width);
		for (int j = 0; j < width; j++) {
			double u = 1.0 - static_cast<double>(i) / height;
			double v = static_cast<double>(j) / width;
			Ray r(origin, low_left_corner + u * vertical + v * horizontal);
			canvas.pixels[i][j] = color(r, world);
		}
	}
	canvas.setImageFormat(ppm);
	canvas.exportTo("../../../Outputs/1.ppm");
	return 0;
}

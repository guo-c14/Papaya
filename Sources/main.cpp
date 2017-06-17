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
#include "Ray.h"
#include "Canvas.h"

using std::vector;

int main(int argc, const char * argv[]) {
	Canvas canvas;
	canvas.pixels = vector<vector<Vector>>(300);
	for (int i = 0; i < 300; i++) {
		canvas.pixels[i] = vector<Vector>(400);
		for (int j = 0; j < 400; j++) {
			double k = i * i + j * j + 2 * i * j;
			canvas.pixels[i][j] = Vector(i * i / k, j * j / k, 2 * i * j / k);
		}
	}
	canvas.setImageFormat(ppm);
	canvas.exportTo("../../../Outputs/1.ppm");
	return 0;
}

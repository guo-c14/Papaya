//
//  main.cpp
//  Papaya
//
//  Created by Guo Chen on 6/17/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include <iostream>
#include "Scene.hpp"

int main(int argc, const char *argv[]) {
	Camera camera;
	int n, width, height;
	Object **list = bezier_curve(camera, n, width, height);
	Object *scene = new BVH(list, n, 0, 1);
	std::cout << "预处理完毕，开始渲染" << std::endl;
#ifdef XCODE
	Canvas canvas(width, height, 8, 64);
	canvas.render(camera, scene, 4);
	canvas.exportImage("../../../Outputs/bezier_curve.ppm", ppm);
#else
	Canvas canvas(width, height, 512, 64);
	canvas.render(camera, scene, 8);
	canvas.exportImage("../Outputs/bezier_curve.ppm", ppm);
#endif
	return 0;
}

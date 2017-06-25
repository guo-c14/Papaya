//
//  main.cpp
//  Papaya
//
//  Created by Guo Chen on 6/17/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include <iostream>
#include "Scene.hpp"
#include "Canvas.hpp"

int main(int argc, const char *argv[]) {
	Camera camera;
	int n, width, height;
	Object **list = bezier_curve(camera, n, width, height);
	Object *scene = new BVH(list, n, 0, 1);
	std::cout << "场景读取完毕，开始渲染" << std::endl;
	Texture *texture = new ImageTexture(TEXTURES_DIRECTORY + "Room.ppm", ppm, 2048, 1024);
	Canvas canvas(width, height, 512, 64, texture);
	canvas.render(camera, scene, 4, true);
	canvas.exportImage(OUTPUTS_DIRECTORY + "bezier_curve.ppm", ppm);
//	Material *china = new GeneralMaterial({0, 1, 0}, new ImageTexture(TEXTURES_DIRECTORY + "China.ppm", ppm, 560, 444), 0.02, {0.5, 0.5, 1}, 1.4);
//	vector<Vec3D> points{{40, 0, 0}, {150, 50, 0}, {150, 150, 0}, {0, 150, 0}, {60, 300, 0}};
//	BezierModel *model = new BezierModel{
//			BezierCurve(points),
//			china
//	};
//	ObjParser parser;
//	parser.write(MODELS_DIRECTORY + "BezierModel.obj", model);
	return 0;
}

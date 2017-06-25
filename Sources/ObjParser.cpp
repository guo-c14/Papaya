//
//  ObjParser.cpp
//  Papaya
//
//  Created by Guo Chen on 6/22/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include "ObjParser.hpp"

BVH *ObjParser::read(const string &file_name, Material *material, double scale) const {
	Object **list;
	int count = 0;
	vector<Vec3D> vertex(1);
	string line;
	ifstream ifs(file_name);
	while (getline(ifs, line, '\n')) {
		stringstream strs(line);
		string key;
		if (!(strs >> key)) {
			continue;
		}
		if (key == "v") {
			double x, y, z;
			strs >> x >> y >> z;
			vertex.push_back({x * scale, y * scale, z * scale});
		}
		if (key == "f") {
			count++;
		}
	}
	ifs.close();
	list = new Object *[count];
	count = 0;
	ifs.open(file_name);
	while (getline(ifs, line, '\n')) {
		stringstream strs(line);
		string key;
		if (!(strs >> key)) {
			continue;
		}
		if (key == "f") {
			int a, b, c;
			strs >> a >> b >> c;
			list[count++] = new Triangle(vertex[a], vertex[b], vertex[c], material);
		}
	}
	return new BVH(list, count, 0, 1);
}

void ObjParser::write(const string &file_name, BezierModel *model) const {
	ofstream ofs;
	ofs.open(file_name, std::ios::out);
	for (double i = 0; i <= 1; i += 0.1) {
		for (double j = 0; j <= 6.2; j += 0.1) {
			Vec3D point = model->pointAt(i, j);
			ofs << "v " << point.x << " " << point.y << " " << point.z << "\n";
		}
	}
	for (int i = 1; i < 569; i += 63) {
		ofs << "f " << i << " " << (i + 63) << " " << (i + 125) << " " << (i + 62) << "\n";
		for (int j = 0; j < 62; j++) {
			ofs << "f " << (i + j) << " " << (i + j + 1) << " " << (i + j + 64) << " " << (i + j + 63) << "\n";
		}
	}
	ofs.close();
}

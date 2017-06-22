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

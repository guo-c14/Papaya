//
//  ObjParser.hpp
//  Papaya
//
//  Created by Guo Chen on 6/22/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef ObjParser_hpp
#define ObjParser_hpp

#include <fstream>
#include <sstream>
#include <string>
#include "BVH.hpp"
#include "Triangle.hpp"
#include "BezierModel.hpp"

using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::string;

class ObjParser {
public:
	BVH *read(const string &file_name, Material *material, double scale = 1) const;
	void write(const string &file_name, BezierModel *model) const;
};

#endif /* ObjParser_hpp */

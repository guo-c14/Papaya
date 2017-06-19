//
//  Canvas.hpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Canvas_hpp
#define Canvas_hpp

#include <string>
#include <vector>
#include "Color.hpp"
#include "ImageIO.hpp"

using std::string;
using std::vector;

class Canvas {
	ImageIO *imageIO;
public:
	vector<vector<Color>> pixels;
	Canvas(ImageIO *imageIO = nullptr);
	void setImageFormat(ImageFormat format);
	void exportImage(const string &fileName) const;
};

#endif /* Canvas_hpp */

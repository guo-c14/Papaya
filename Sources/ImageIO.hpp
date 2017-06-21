//
//  ImageIO.hpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef ImageIO_hpp
#define ImageIO_hpp

#include <string>
#include <vector>
#include "Color.hpp"

using std::string;
using std::vector;

enum ImageFormat {
	bmp, jpg, png, ppm
};

class ImageIO {
public:
	virtual void importImage(vector<vector<Vec3D>> &pixels, const string &fileName) = 0;
	virtual void exportImage(const vector<vector<Vec3D>> &pixels, const string &fileName) = 0;
};

class BMPIO: public ImageIO {
public:
	virtual void importImage(vector<vector<Vec3D>> &pixels, const string &fileName);
	virtual void exportImage(const vector<vector<Vec3D>> &pixels, const string &fileName);
};

class JPGIO: public ImageIO {
public:
	virtual void importImage(vector<vector<Vec3D>> &pixels, const string &fileName);
	virtual void exportImage(const vector<vector<Vec3D>> &pixels, const string &fileName);
};

class PNGIO: public ImageIO {
public:
	virtual void importImage(vector<vector<Vec3D>> &pixels, const string &fileName);
	virtual void exportImage(const vector<vector<Vec3D>> &pixels, const string &fileName);
};

class PPMIO: public ImageIO {
public:
	virtual void importImage(vector<vector<Vec3D>> &pixels, const string &fileName);
	virtual void exportImage(const vector<vector<Vec3D>> &pixels, const string &fileName);
};

#endif /* ImageIO_hpp */

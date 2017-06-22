//
//  Canvas.hpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Canvas_hpp
#define Canvas_hpp

#include "Camera.hpp"
#include "Object.hpp"
#include "ImageIO.hpp"
#include "Texture.hpp"

class Canvas {
protected:
	Texture *texture;
	int width, height;
	int samples_per_pixel;
	int iteration_depth;
	Camera camera;
	Object *scene;
	vector<vector<Vec3D>> pixels;
	void callFromThread(int start_row, int end_row);
	Vec3D computeColor(const Ray &ray, const Object *scene, int depth);
public:
	Canvas(int width = 800, int height = 450, int samples_per_pixel = 128,
		int iteration_depth = 64);
	void render(const Camera &camera, Object *scene, int threads_num = 4);
	void exportImage(const string &fileName, ImageFormat format) const;
};

#endif /* Canvas_hpp */

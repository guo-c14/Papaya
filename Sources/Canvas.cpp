//
//  Canvas.cpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include "Canvas.hpp"

Canvas::Canvas(ImageIO *imageIO): imageIO(imageIO) {}

void Canvas::setImageFormat(ImageFormat format) {
	switch (format) {
		case bmp:
			imageIO = new BMPIO;
			break;
		case jpg:
			imageIO = new JPGIO;
			break;
		case png:
			imageIO = new PNGIO;
			break;
		case ppm:
			imageIO = new PPMIO;
			break;
	}
}

void Canvas::exportImage(const string &fileName) const {
	imageIO->exportImage(pixels, fileName);
}

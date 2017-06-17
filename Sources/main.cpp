//
//  main.cpp
//  Papaya
//
//  Created by Guo Chen on 6/17/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include <iostream>
#include "Vector.h"
#include "Ray.h"

int main(int argc, const char * argv[]) {
	Vector v(1, 2, 2);
	Vector b(2, 2, 1);
	Ray ray(v, b);
	std::cout << ray << std::endl;
	std::cout << ray.pointAt(3) << std::endl;
	return 0;
}

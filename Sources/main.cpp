//
//  main.cpp
//  Papaya
//
//  Created by Guo Chen on 6/17/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include <iostream>
#include "Vector.h"

int main(int argc, const char * argv[]) {
	Vector v(1, 2, 2);
	Vector b(2, 2, 1);
	std::cout << dot(v, b) << std::endl;
	std::cout << cross(v, b) << std::endl;
	std::cout << distance(v, b) << std::endl;
	std::cout << distance2(v, b) << std::endl;
	std::cout << v.norm() << std::endl;
	std::cout << v.norm2() << std::endl;
	std::cout << v.normalize() << std::endl;
	return 0;
}

//
//  Utility.cpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include <ctime>
#include <random>
#include <functional>
#include "Utility.hpp"

double drand() {
	static auto engine = std::bind(
		std::uniform_real_distribution<double>{0, 0.9999999999999999},
		std::default_random_engine()
	);
	return engine();
}

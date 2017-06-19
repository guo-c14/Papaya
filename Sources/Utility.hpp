//
//  Utility.hpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef Utility_hpp
#define Utility_hpp

const double PI = 3.141592653589793;
const double PI_180 = 0.017453292519943295;
const double PI_360 = 0.008726646259971648;

double drand();

inline double ddmin(double a, double b) {
	return a < b ? a : b;
}

inline double ddmax(double a, double b) {
	return a > b ? a : b;
}

#endif /* Utility_hpp */

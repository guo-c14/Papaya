//
//  config.hpp
//  Papaya
//
//  Created by Guo Chen on 6/25/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#ifndef config_hpp
#define config_hpp

#include <string>

using std::string;

#ifdef XCODE
const string OUTPUTS_DIRECTORY = "../../../Outputs/";
const string MODELS_DIRECTORY = "../../../Models/";
const string TEXTURES_DIRECTORY = "../../../Textures/";
#else
const string OUTPUTS_DIRECTORY = "../Outputs/";
const string MODELS_DIRECTORY = "../Models/";
const string TEXTURES_DIRECTORY = "../Textures/";
#endif

#endif /* config_hpp */

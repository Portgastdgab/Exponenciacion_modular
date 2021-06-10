/*
File:        main.cpp
Description: this file executes the program
Created:     2021-06-09 10:58:09
Author:      José Vilca Campana <@marcusmors>
Mail:        alivezeh@gmail.com

This file is part of Exponenciacion_modular.
Exponenciacion_modular is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

Exponenciacion_modular is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Exponenciacion_modular.  If not, see <https://www.gnu.org/licenses/>.
*/

// A simple program that computes the square root of a number
#include <cmath>
#include <iostream>
#include <string>

#include "TutorialConfig.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		// report version
		std::cout << argv[0] << " Version " << Tutorial_VERSION_MAJOR << "."
				  << Tutorial_VERSION_MINOR << std::endl;
		std::cout << "Usage: " << argv[0] << " number" << std::endl;
		return 1;
	}

	// convert input to double
	const double inputValue = std::stod(argv[1]);

	// calculate square root
	const double outputValue = sqrt(inputValue);
	std::cout << "The square root of " << inputValue << " is " << outputValue
			  << std::endl;
	return 0;
}

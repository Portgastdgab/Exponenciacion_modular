#ifndef __POWER_MODULE_HPP__
#define __POWER_MODULE_HPP__

/*
File:        min_sum_chain.cpp
Description: Implementation to find the minimum sum chain.
Created:     2021-06-09 11:01:09
Author:      José Vilca Campana <@marcusmors>
Mail:        alivezeh@gmail.com

// code from stbrumme for euler's problem 122: https://euler.stephan-brumme.com/122/
// repository https://github.com/stbrumme/euler/blob/master/euler-0122.cpp

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

#include <vector>
#include <map>
#include <NTL/ZZ.h>

using namespace NTL;

namespace MOD
{
	typedef std::vector<unsigned int> Chain;

	class PowerModule
	{
	private:
		// iterative depth-first search of Brauer sequence
		bool search(Chain &, unsigned, unsigned);

		// increase depth until a solution is found
		Chain findChain(unsigned int exponent);

	public:
		ZZ empower(ZZ, unsigned);
	};
}
// a single addition chain

#endif // __POWER_MODULE_HPP__

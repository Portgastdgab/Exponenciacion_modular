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

#include "power_module.hpp"
#include <vector>
#include <map>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

// iterative depth-first search of Brauer sequence
bool MOD::PowerModule::search(Chain &chain, unsigned exponent, unsigned maxDepth)
{
	// too deep ?
	if (chain.size() > maxDepth)
		return false;

	auto last = chain.back();
	for (size_t i = 0; i < chain.size(); i++)
	{
		//auto sum = chain[i] + last;
		auto sum = chain[chain.size() - 1 - i] + last; // try high exponents first => about twice as fast
		if (sum == exponent)
			return true;

		chain.push_back(sum);
		if (search(chain, exponent, maxDepth))
			return true;

		chain.pop_back();
	}

	return false;
}

// increase depth until a solution is found
MOD::Chain MOD::PowerModule::findChain(unsigned int exponent)
{
	// cached ? (needed for Hackerrank only)
	static std::map<unsigned int, Chain> cache;
	auto lookup = cache.find(exponent);
	if (lookup != cache.end())
		return lookup->second;

	// start iterative search
	Chain chain;
	unsigned int depth = 1;
	while (true)
	{
		// reset chain
		chain = {1};
		// a start search
		if (search(chain, exponent, depth))
			break;

		// failed, allow to go one step deeper
		depth++;
	}

	cache[exponent] = chain;
	return chain;
}

ZZ MOD::PowerModule::empower(ZZ base, unsigned exponent)
{
	auto chain = findChain(exponent);
	ZZ resultChain[chain.size()] = {base, base * base};
	for (unsigned i = 2; i < chain.size(); i++)
	{
		auto sum = chain[i];
		const unsigned exp1_index = i - 1;
		const unsigned exp2 = sum - chain[exp1_index];
		unsigned exp2_index;
		for (unsigned j = 0; j < chain.size(); j++)
			if (exp2 == chain[j])
			{
				exp2_index = j;
				break;
			}

		ZZ mult1 = resultChain[exp1_index];
		ZZ mult2 = resultChain[exp2_index];
		resultChain[i] = mult1 * mult2;
		// resultChain[i] = resultChain[i-1] * resultChain[resultChain[i-1]]
	}
	return resultChain[chain.size() - 1];
}

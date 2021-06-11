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

#include <vector>
#include <map>
#include <NTL/ZZ.h>

using namespace NTL;
using namespace std;

// a single addition chain
typedef std::vector<ZZ> Chain;

class PowerModule
{
private:
	// iterative depth-first search of Brauer sequence
	bool search(Chain &, ZZ, unsigned int);

	// increase depth until a solution is found
	Chain findChain(ZZ exponent);

public:
	ZZ empower(ZZ, ZZ);
};

// iterative depth-first search of Brauer sequence
bool PowerModule::search(Chain &chain, ZZ exponent, unsigned int maxDepth)
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
Chain PowerModule::findChain(ZZ exponent)
{
	// cached ? (needed for Hackerrank only)
	static std::map<ZZ, Chain> cache;
	auto lookup = cache.find(exponent);
	if (lookup != cache.end())
		return lookup->second;

	// start iterative search
	Chain chain;
	unsigned int depth = 1;
	while (true)
	{
		// reset chain
		chain = {ZZ(1)};
		// a start search
		if (search(chain, exponent, depth))
			break;

		// failed, allow to go one step deeper
		depth++;
	}

	cache[exponent] = chain;
	return chain;
}

ZZ PowerModule::empower(ZZ base, ZZ exponent)
{
	auto chain = findChain(exponent);
	ZZ resultChain[chain.size()] = {base, base * base};
	for (unsigned i = 2; i < chain.size(); i++)
	{
		auto sum = chain[i];
		const unsigned exp1_index = i - 1;
		const ZZ exp2 = ZZ(sum - chain[exp1_index]);
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

int main()
{
	ZZ base = ZZ(197564123456785645645675645345675645679);
	ZZ exponent = ZZ(277897456412375674564126789756456378975);

	cout << PowerModule().empower(base, exponent) << endl;
	return 0;
}

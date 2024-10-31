#include "TestFunctions.h"

uint32_t ReverseModule(uint32_t a, uint32_t m)
{
	return [](uint32_t x, uint32_t degree)
	{
		uint32_t result{ 1 };
		for (int i = 0; i < degree; i++) result *= x;
		return result;
	} (a, m - 2) % m;
}

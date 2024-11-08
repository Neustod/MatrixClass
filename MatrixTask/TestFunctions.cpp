#include "TestFunctions.h"

uint32_t ReverseModule(uint32_t a, uint32_t m)
{
	uint32_t result{ 1 };
	for (int i = 0; i < m - 2; i++) result *= a;
	return result % m;
}

#pragma once
#include <cstdint>

class IntRandomizer
{
public:
	IntRandomizer();

	int16_t RandInt16();

	int32_t RandInt32();

	int16_t RandInt16(int16_t lBorder, int16_t rBorder);

	int32_t RandInt32(int32_t lBorder, int32_t rBorder);
};


#include "IntRandomizer.h"
#include "RandSeed.h"
#include <time.h>
#include <stdlib.h>


IntRandomizer::IntRandomizer() { RandSeed::Instance(); }

int16_t IntRandomizer::RandInt16() { return rand(); }

int32_t IntRandomizer::RandInt32() { return (rand() << 16) + rand(); }

int16_t IntRandomizer::RandInt16(int16_t lBorder, int16_t rBorder) 
{
	return rand() % (rBorder - lBorder) + lBorder;
}


int32_t IntRandomizer::RandInt32(int32_t lBorder, int32_t rBorder)
{
	return ((rand() << 16) + rand()) % (rBorder - lBorder) + lBorder;
}

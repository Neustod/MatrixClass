#include "Randomizer.h"
#include <time.h>
#include <stdlib.h>

Randomizer::Randomizer() 
{
	srand(time(0));
}

Randomizer& Randomizer::Instance()
{
	static Randomizer instance;
	return instance;
}

int Randomizer::RandInt(int lBorder, int rBorder) 
{
	return rand() % (rBorder - lBorder) + lBorder;
}

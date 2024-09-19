#include "RandSeed.h"
#include <time.h>
#include <stdlib.h>


RandSeed::RandSeed()
{
	srand(time(0));
}

RandSeed& RandSeed::Instance() {
	static RandSeed instance;
	return instance;
}
#pragma once
class Randomizer
{
private:
	Randomizer();

public:
	static Randomizer& Instance();

	int RandInt(int lBorder, int rBorder);

	Randomizer(const Randomizer&) = delete;
	void operator=(const Randomizer&) = delete;
};


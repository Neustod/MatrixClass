#pragma once

// Singletone base for IntRandomizer.
class RandSeed
{
private:
	RandSeed();

public:
	static RandSeed& Instance();

	RandSeed(const RandSeed&) = delete;
	void operator=(const RandSeed&) = delete;
};


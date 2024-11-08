#include "RNSVector.h"
#include <xmemory>
#include <iostream>
#include <vector>
#include <string>
#include "TestFunctions.h"

#ifdef _DEBUG
#define DEBUG(x) x
#else
#define DEBUG(x)
#endif // _DEBUG


// Constructors

RNSVector::RNSVector(const std::shared_ptr<RNSCrypter>& crypter, uint32_t decNum) : _crypter(crypter)
{
	_size = _crypter.get()->Size();
	_primes = _crypter.get()->Primes();

	_digits = new uint8_t[_size];
	_crypter.get()->Encode(_digits, decNum);

	_overflowBank = new uint8_t[_size];
	memset(_overflowBank, '\0', _size * sizeof(uint8_t));
}

RNSVector::RNSVector(const RNSVector& src) : _crypter(src._crypter)
{
	_size = _crypter.get()->Size();
	_primes = _crypter.get()->Primes();

	_digits = new uint8_t[_size];
	memcpy(_digits, src._digits, _size * sizeof(uint8_t));

	_overflowBank = new uint8_t[_size];
	memcpy(_overflowBank, src._overflowBank, _size * sizeof(uint8_t));
}

RNSVector::RNSVector(RNSVector&& src) noexcept : _crypter(std::move(src._crypter))
{
	_size = _crypter.get()->Size();
	_primes = _crypter.get()->Primes();

	_digits = NULL;
	std::swap(_digits, src._digits);

	_overflowBank = NULL;
	std::swap(_overflowBank, src._overflowBank);
}


// Encoding and Decoding

uint32_t RNSVector::Decode() { return _crypter.get()->Decode(_digits); }

void RNSVector::Encode(uint32_t decNum) { _crypter.get()->Encode(_digits, decNum); }


// Arithmetical operations

void RNSVector::Add(const RNSVector& rightRnsNum)
{
	if (_size != rightRnsNum._size) throw std::exception("RNSVector.Add: Different vector sizes.");

	uint16_t extension{ 0 };

	for (auto i = 0; i < _size; i++) 
	{
		extension = ((uint16_t)_digits[i] + rightRnsNum._digits[i]);
		_overflowBank[i] += (extension >> 8) + rightRnsNum._overflowBank[i];
		_digits[i] = (uint8_t)extension;
	}
}

void RNSVector::Sub(const RNSVector& rightRnsNum)
{
	if (_size != rightRnsNum._size) throw std::exception("RNSVector.Add: Different vector sizes.");

	for (auto i = 0; i < _size; i++)
	{
		_overflowBank[i] += -(_digits[i] < rightRnsNum._digits[i]) - rightRnsNum._overflowBank[i];
		_digits[i] = _digits[i] - rightRnsNum._digits[i];
	}
}

void RNSVector::Mul(const RNSVector& rightRnsNum)
{
	if (_size != rightRnsNum._size) throw std::exception("RNSVector.Add: Different vector sizes.");

	uint16_t extension{ 0 };

	for (auto i = 0; i < _size; i++)
	{
		extension = ((uint16_t)_digits[i] * rightRnsNum._digits[i]);
		_overflowBank[i] += (extension >> 8) + rightRnsNum._overflowBank[i];
		_digits[i] = (uint8_t)(extension % 256);
	}
}

// TODO: [RNSVector.Div] remove dependences from bases
void RNSVector::Div(const RNSVector& rightRnsNum)
{
	for (auto i = 0; i < _size; i++)
	{
		if (_digits[i] == 0) continue;

		for (int prime = 1; prime < _crypter.get()->Primes()[i]; prime++)
		{
			if ((prime * rightRnsNum._digits[i]) % _primes[i] == _digits[i])
			{
				_digits[i] = prime;
				break;
			}

			if (prime == _crypter.get()->Primes()[i] - 1) throw std::exception("RNSVector.Div: unable to calculate the result.");
		}
	}
}

// TODO: [RNSVector.DivByTwo] get rid of bases
bool RNSVector::DivByTwo()
{
	for (auto i = 0; i < _size; i++)
	{
		if (_digits[i] == 0) continue;

		for (int prime = 1; prime < _primes[i]; prime++)
		{
			if ((prime << 1) % _primes[i] == _digits[i])
			{
				_digits[i] = prime;
				break;
			}
			
			if (prime == _primes[i] - 1) return false;
		}
	}
	return true;
}

// TODO: [RNSVector.Pow] get rid of bases
void RNSVector::Pow(uint32_t degree)
{
	if (degree == 0) { for (auto i = 0; i < _size; i++) _digits[i] = 1; return; };
	if (degree == 1) return;

	uint32_t tmp{ 0 };

	for (auto i = 0; i < _size; i++) 
	{
		tmp = _digits[i];

		for (auto j = 0; j < degree - 1; j++) 
		{
			_digits[i] = (_digits[i] * tmp) % _primes[i];
		}
	}
}

RNSVector& RNSVector::OverflowCorrection(const RNSVector& errorValue)
{
	uint16_t extension{ 0 };

	for (auto i = 0; i < _size; i++) 
	{
		extension = _digits[i] + (uint16_t)_overflowBank[i] * errorValue[i];
		_digits[i] = extension % 256;

		_overflowBank[i] = 0;
	}

	return *this;
}

RNSVector& RNSVector::Normalize()
{
	for (auto i = 0; i < _size; i++) 
	{ 
		_digits[i] %= _primes[i];
	}

	return *this;
}

// TODO: [RNSVector.DivisionDeep] get rid of Normalization
uint8_t RNSVector::DivisionDeep(uint32_t maxDeep) const
{
	RNSVector err{ _crypter, 256 };

	uint32_t deep{ 0 };
	size_t currSize{ 0 };

	auto IsNumber = [](const RNSVector& rns, uint32_t number)
	{
		for (auto i = 0; i < rns.Size(); i++)
			if (rns[i] != number) return false;
		return true;
	};

	if (IsNumber(*this, 0)) return 0;

	std::vector<RNSVector> nums;

	nums.push_back(RNSVector{ *this });

	while (deep < maxDeep) 
	{
		currSize = nums.size();
		nums.reserve(currSize << 1);

		for (auto i = 0; i < currSize; i++)
		{
			if (IsNumber(nums[i], 1)) return deep;

			nums.emplace_back(nums[i]);
			(--nums[nums.size() - 1]).OverflowCorrection(err).Normalize();

			nums[i].DivByTwo();
			nums.back().DivByTwo();
		}

		deep++;
	}

	return maxDeep;
}


// TODO: [RNSVector.DeepCompare] get rid of Normalization
int RNSVector::DeepCompare(const RNSVector rnsRight, uint32_t maxDeep) const
{
	RNSVector err{ _crypter, 256 };
	RNSVector rnsLeft{ *this };

	uint32_t leftDeep = this->DivisionDeep(maxDeep);
	uint32_t rightDeep = rnsRight.DivisionDeep(leftDeep + 1);
	uint32_t resultDeep{ 0 };

	if (leftDeep == rightDeep) 
	{
		rnsLeft -= rnsRight;
		resultDeep = rnsLeft.OverflowCorrection(err).Normalize().DivisionDeep(leftDeep + 1);

		return (resultDeep == 0) * rnsLeft[0] + (resultDeep != 0) * (leftDeep - resultDeep);
	}

	return leftDeep - rightDeep;
}


void RNSVector::Input(std::ifstream& fin)
{
	for (auto i = 0; i < _size; i++) fin >> _digits[i];
}

void RNSVector::Output(std::ofstream& fout) const
{
	for (auto i = 0; i < _size; i++)
	{
		fout << _digits[i];

		if (i < _size - 1) fout << " ";
	}
}

std::string RNSVector::ToString() const
{
	std::string result{ "" };

	for (size_t i = 0; i < _size; i++)
	{
		result += std::to_string(_digits[i]);
		if (i != _size - 1) result.push_back(' ');
	}

	return result;
}


bool RNSVector::operator==(const RNSVector& right) const
{
	if (_size != right._size) return false;

	for (auto i = 0; i < _size; i++) 
	{
		if (_digits[i] != right._digits[i]) return false;
	}

	return true;
}


void RNSVector::operator=(const RNSVector& src)
{
	if (this == &src) return;

	_size = src._size;
	_crypter = src._crypter;

	if (_digits != nullptr || _overflowBank != nullptr) 
	{
		delete[] _digits;
		delete[] _overflowBank;
	}

	_digits = new uint8_t[_size];
	_overflowBank = new uint8_t[_size];

	memcpy(_digits, src._digits, _size * sizeof(uint8_t));
	memcpy(_overflowBank, src._overflowBank, _size * sizeof(uint8_t));
}

void RNSVector::operator=(RNSVector&& src) noexcept
{
	_size = src._size;
	_crypter = std::move(src._crypter);

	std::swap(_digits, src._digits);
	std::swap(_overflowBank, src._overflowBank);
}


// Deconstructor

RNSVector::~RNSVector()
{
	if (_digits != NULL) delete[] _digits;
	if (_overflowBank != NULL) delete[] _overflowBank;
}

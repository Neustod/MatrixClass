#include "RNSVectorLight.h"
#include <vector>
#include <string>


RNSVectorLight::RNSVectorLight(size_t size) : _size(size), _digits(nullptr), _overflowBank(nullptr)
{
	if (_size > 0) 
	{
		_digits = new unsigned char[_size];
		_overflowBank = new unsigned char[_size];

		memset(_digits, 0, sizeof(unsigned char) * _size);
		memset(_overflowBank, 0, sizeof(unsigned char) * _size);
	}
}

RNSVectorLight::RNSVectorLight(const unsigned char* digits, size_t size) : _size(0), _digits(nullptr), _overflowBank(nullptr)
{
	SetDigits(digits, size);
}

RNSVectorLight::~RNSVectorLight()
{
	if (_digits != nullptr) delete[] _digits;
	if (_overflowBank != nullptr) delete[] _overflowBank;
}

RNSVectorLight::RNSVectorLight(const RNSVectorLight& src) : _size(src._size), _digits(nullptr), _overflowBank(nullptr)
{
	if (_size > 0)
	{
		_digits = new unsigned char[_size];
		_overflowBank = new unsigned char[_size];

		memcpy(_digits, src._digits, sizeof(unsigned char) * _size);
		memcpy(_overflowBank, src._overflowBank, sizeof(unsigned char) * _size);
	}
}

RNSVectorLight::RNSVectorLight(RNSVectorLight&& src) noexcept : _size(src._size), _digits(nullptr), _overflowBank(nullptr)
{
	std::swap(_digits, src._digits);
	std::swap(_overflowBank, src._overflowBank);
}

void RNSVectorLight::operator=(const RNSVectorLight& src)
{
	if (this == &src || (_size == 0 && src._size == 0)) return;

	if (src._size == 0) 
	{
		delete[] _digits;
		delete[] _overflowBank;

		_size = 0;
		_digits = nullptr;
		_overflowBank = nullptr;

		return;
	}

	if (_size != src._size)
	{
		if (_digits != nullptr) 
		{
			delete[] _digits;
			delete[] _overflowBank;
		}

		_size = src._size;
		_digits = new unsigned char[_size];
		_overflowBank = new unsigned char[_size];
	}

	memcpy(_digits, src._digits, sizeof(unsigned char) * _size);
	memcpy(_overflowBank, src._overflowBank, sizeof(unsigned char) * _size);
}

void RNSVectorLight::operator=(RNSVectorLight&& src) noexcept
{
	_size = src._size;

	std::swap(_digits, src._digits);
	std::swap(_overflowBank, src._overflowBank);
}

void RNSVectorLight::SetDigits(const unsigned char* digits, size_t size)
{
	if (_size == 0 && size == 0) return;

	if (_size != size) 
	{
		if (_size > 0) 
		{
			delete[] _digits;
			delete[] _overflowBank;

			_digits = nullptr;
			_overflowBank = nullptr;
		}

		_size = size;

		if (size > 0) 
		{
			_digits = new unsigned char[size];
			_overflowBank = new unsigned char[size];
		}
	}

	if (size > 0) 
	{
		memcpy(_digits, digits, sizeof(unsigned char) * size); 
		memset(_overflowBank, 0, sizeof(unsigned char) * size);
	}
}


// Arithmetical operations

void RNSVectorLight::Add(const RNSVectorLight& rightRnsNum)
{
	if (_size != rightRnsNum._size) throw std::exception("RNSVectorLight.Add: Different vector sizes.");

	uint16_t extension{ 0 };

	for (auto i = 0; i < _size; i++)
	{
		extension = ((uint16_t)_digits[i] + rightRnsNum._digits[i]);
		_overflowBank[i] += (extension >> 8) + rightRnsNum._overflowBank[i];
		_digits[i] = (uint8_t)extension;
	}
}

void RNSVectorLight::Sub(const RNSVectorLight& rightRnsNum)
{
	if (_size != rightRnsNum._size) throw std::exception("RNSVectorLight.Sub: Different vector sizes.");

	for (auto i = 0; i < _size; i++)
	{
		_overflowBank[i] += -(_digits[i] < rightRnsNum._digits[i]) - rightRnsNum._overflowBank[i];
		_digits[i] = _digits[i] - rightRnsNum._digits[i];
	}
}

void RNSVectorLight::Mul(const RNSVectorLight& rightRnsNum)
{
	if (_size != rightRnsNum._size) throw std::exception("RNSVectorLight.Mul: Different vector sizes.");

	uint16_t extension, extensionR;

	for (auto i = 0; i < _size; i++)
	{
		extension = (uint16_t)_digits[i] + ((uint16_t)_overflowBank[i] << 8);
		extensionR = (uint16_t)rightRnsNum._digits[i] + ((uint16_t)rightRnsNum._overflowBank[i] << 8);

		extension *= extensionR;
		_overflowBank[i] += (extension >> 8);
		_digits[i] = (uint8_t)extension;
	}
}

void RNSVectorLight::Div(const unsigned char* dividerToReverse)
{
	uint16_t extension{ 0 };

	for (auto i = 0; i < _size; i++)
	{
		extension = ((uint16_t)_digits[i] * dividerToReverse[i]);
		_overflowBank += extension >> 8;
		_digits[i] = extension;
	}
}

void RNSVectorLight::Div(const RNSVectorLight& dividerToReverse)
{
	if (_size != dividerToReverse._size) throw std::exception("RNSVectorLight.Div: Different vector sizes.");

	Div(dividerToReverse._digits);
}

RNSVectorLight& RNSVectorLight::OverflowCorrection(const unsigned char* overflowErrorValue)
{
	unsigned short int extension{ 0 };

	for (auto i = 0; i < _size; i++)
	{
		extension = _digits[i] + (uint16_t)_overflowBank[i] * overflowErrorValue[i];
		_overflowBank[i] = extension >> 8;
		_digits[i] = extension % 256;

		if (_overflowBank[i] > 0) --i;
	}

	return *this;
}

RNSVectorLight& RNSVectorLight::SingleOverflowCorrection(const unsigned char* overflowErrorValue)
{
	unsigned short int extension{ 0 };

	for (auto i = 0; i < _size; i++)
	{
		extension = _digits[i] + (uint16_t)_overflowBank[i] * overflowErrorValue[i];
		_overflowBank[i] = extension >> 8;
		_digits[i] = extension % 256;
	}

	return *this;
}

//unsigned char RNSVectorLight::DivisionDeep(const unsigned char* overflowErrorValue, const unsigned char* rnsReverseModuleOfTwo, unsigned int maxDeep) const
//{
//	uint32_t deep{ 0 };
//	size_t currSize{ 0 };
//
//	auto IsNumber = [](const RNSVectorLight& rns, uint32_t number)
//	{
//		for (auto i = 0; i < rns.Size(); i++)
//			if (rns[i] != number) return false;
//		return true;
//	};
//
//	if (IsNumber(*this, 0)) return 0;
//
//	std::vector<RNSVectorLight> nums;
//
//	nums.push_back(RNSVectorLight{ *this });
//
//	while (deep < maxDeep)
//	{
//		currSize = nums.size();
//		nums.reserve(currSize << 1);
//
//		for (auto i = 0; i < currSize; i++)
//		{
//			if (IsNumber(nums[i], 1)) return deep;
//
//			nums.emplace_back(nums[i]);
//			(--nums[nums.size() - 1]).OverflowCorrection(overflowErrorValue);
//
//			nums[i].Div(rnsReverseModuleOfTwo);
//			nums.back().Div(rnsReverseModuleOfTwo);
//		}
//
//		deep++;
//	}
//
//	return maxDeep;
//}

//unsigned char RNSVectorLight::DivisionDeep(const RNSVectorLight& overflowErrorValue, const RNSVectorLight& rnsReverseModuleOfTwo, unsigned int maxDeep) const
//{
//	return DivisionDeep(overflowErrorValue._digits, rnsReverseModuleOfTwo._digits, maxDeep);
//}

//int RNSVectorLight::DeepCompare(const unsigned char* overflowErrorValue, const unsigned char* rnsReverseModuleOfTwo, const RNSVectorLight& rnsRight, unsigned int maxDeep) const
//{
//	RNSVectorLight rnsLeft{ *this };
//
//	unsigned int leftDeep = this->DivisionDeep(overflowErrorValue, rnsReverseModuleOfTwo, maxDeep);
//	unsigned int rightDeep = rnsRight.DivisionDeep(overflowErrorValue, rnsReverseModuleOfTwo, leftDeep + 1);
//	unsigned int resultDeep{ 0 };
//
//	if (leftDeep == rightDeep)
//	{
//		rnsLeft -= rnsRight;
//		resultDeep = rnsLeft.OverflowCorrection(overflowErrorValue).DivisionDeep(overflowErrorValue, rnsReverseModuleOfTwo, leftDeep + 1);
//
//		return (resultDeep == 0) * rnsLeft[0] + (resultDeep != 0) * (leftDeep - resultDeep);
//	}
//
//	return leftDeep - rightDeep;
//}

//int RNSVectorLight::DeepCompare(const RNSVectorLight& overflowErrorValue, const RNSVectorLight& rnsReverseModuleOfTwo, const RNSVectorLight& rnsRight, unsigned int maxDeep) const
//{
//	return DeepCompare(overflowErrorValue._digits, rnsReverseModuleOfTwo._digits, rnsRight, maxDeep);
//}

void RNSVectorLight::Input(std::ifstream& fin)
{
	for (auto i = 0; i < _size; i++) fin >> _digits[i];
}

void RNSVectorLight::Output(std::ofstream& fout) const
{
	for (auto i = 0; i < _size; i++)
	{
		fout << _digits[i];

		if (i < _size - 1) fout << " ";
	}
}

std::string RNSVectorLight::ToString() const
{
	std::string result{ "" };

	for (size_t i = 0; i < _size; i++)
	{
		result += std::to_string(_digits[i]);
		if (i != _size - 1) result.push_back(' ');
	}

	return result;
}

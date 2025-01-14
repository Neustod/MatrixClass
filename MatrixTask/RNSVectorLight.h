#pragma once
#include <fstream>


class RNSVectorLight 
{
private:
	unsigned char* _digits;
	unsigned char* _overflowBank;

	size_t _size;

public:
	RNSVectorLight(size_t size = 0);

	RNSVectorLight(const unsigned char* digits, size_t size);

	~RNSVectorLight();

	RNSVectorLight(const RNSVectorLight& src);

	RNSVectorLight(RNSVectorLight&& src) noexcept;

	void operator=(const RNSVectorLight& src);

	void operator=(RNSVectorLight&& src) noexcept;

public:
	size_t Size() const { return _size; };

	const unsigned char* Digits() const { return _digits; }

	unsigned char* Digits() { return _digits; }

public:
	void SetDigits(const unsigned char* digits, size_t size);

public:
	// Local adding operation for RNS numbers.
	void Add(const RNSVectorLight& rightRnsNum);

	// Local subliming operation for RNS numbers.
	void Sub(const RNSVectorLight& rightRnsNum);

	// Local multiplicating operation for RNS numbers.
	void Mul(const RNSVectorLight& rightRnsNum);

	// Local multiplicating operation for RNS numbers.
	void Div(const unsigned char* dividerToReverse);

	// Local multiplicating operation for RNS numbers.
	void Div(const RNSVectorLight& dividerToReverse);


public:
	// Overflow correction
	RNSVectorLight& OverflowCorrection(const unsigned char* overflowErrorValue);

	RNSVectorLight& SingleOverflowCorrection(const unsigned char* overflowErrorValue);

	// Overflow correction
	RNSVectorLight& OverflowCorrection(const RNSVectorLight& overflowErrorValue) 
	{
		return OverflowCorrection(overflowErrorValue._digits);
	}

	RNSVectorLight& SingleOverflowCorrection(const RNSVectorLight& overflowErrorValue) 
	{
		return SingleOverflowCorrection(overflowErrorValue._digits);
	}

	bool OverflowFlag(size_t index) { return _overflowBank[index] != 0; }

public:
	//unsigned char DivisionDeep(const unsigned char* overflowErrorValue, const unsigned char* rnsReverseModuleOfTwo, unsigned int maxDeep) const;

	//unsigned char DivisionDeep(const RNSVectorLight& overflowErrorValue, const RNSVectorLight& rnsReverseModuleOfTwo, unsigned int maxDeep) const;

	//int DeepCompare(const unsigned char* overflowErrorValue, const unsigned char* rnsReverseModuleOfTwo, const RNSVectorLight& rnsRight, unsigned int maxDeep) const;

	//int DeepCompare(const RNSVectorLight& overflowErrorValue, const RNSVectorLight& rnsReverseModuleOfTwo, const RNSVectorLight& rnsRight, unsigned int maxDeep) const;

public:
	void Input(std::ifstream& fin);

	void Output(std::ofstream& fout) const;

	std::string ToString() const;

	friend std::string to_string(const RNSVectorLight& item) { return item.ToString(); };

public:
	inline friend RNSVectorLight& operator+(const RNSVectorLight& left, const RNSVectorLight& right)
	{
		RNSVectorLight* result = new RNSVectorLight(left);
		result->Add(right);

		return *result;
	}

	inline friend RNSVectorLight& operator-(const RNSVectorLight& left, const RNSVectorLight& right)
	{
		RNSVectorLight* result = new RNSVectorLight(left);
		result->Sub(right);

		return *result;
	}

	inline friend RNSVectorLight& operator*(const RNSVectorLight& left, const RNSVectorLight& right)
	{
		RNSVectorLight* result = new RNSVectorLight(left);
		result->Mul(right);

		return *result;
	}

	inline void operator+=(const RNSVectorLight& right) { this->Add(right); }

	inline void operator-=(const RNSVectorLight& right) { this->Sub(right); }

	inline void operator*=(const RNSVectorLight& right) { this->Mul(right); }

	inline RNSVectorLight& operator++()
	{
		for (size_t i = 0; i < _size; i++)
		{
			_overflowBank[i] += (_digits[i] == 255);
			_digits[i] = (_digits[i] + 1);
		}

		return *this;
	}

	inline RNSVectorLight& operator++(int)
	{
		RNSVectorLight& result = *new RNSVectorLight{ *this };

		++* this;

		return result;
	}

	inline RNSVectorLight& operator--()
	{
		for (size_t i = 0; i < _size; i++)
		{
			_overflowBank[i] -= (_digits[i] == 0);
			--_digits[i];
		}

		return *this;
	}

	inline RNSVectorLight& operator--(int)
	{
		RNSVectorLight& result = *new RNSVectorLight{ *this };

		--* this;

		return result;
	}

	bool operator==(const RNSVectorLight& right) const 
	{
		if (_size != right._size) return false;

		for (auto i = 0; i < _size; i++)
			if (_digits[i] != right._digits[i]) return false;

		return true;
	};

	bool operator!=(const RNSVectorLight& right) const { return !(*this == right); };

	uint8_t operator[](size_t index) const
	{
		if (index >= _size) throw std::exception("RNSVector.operator[]: index out of range.");
		return _digits[index];
	}

	uint8_t& operator[](size_t index)
	{
		if (index >= _size) throw std::exception("RNSVector.operator[]: index out of range.");
		return _digits[index];
	}

public:
	friend std::ostream& operator<<(std::ostream& out, const RNSVectorLight& item)
	{
		for (size_t i = 0; i < item.Size(); i++) out << item[i];
		return out;
	}

	friend std::istream& operator>>(std::istream& in, RNSVectorLight& item)
	{
		for (size_t i = 0; i < item.Size(); i++) in >> item[i];
		return in;
	}
};
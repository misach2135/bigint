#ifndef BIGINT_H
#define BIGINT_H

#include <cstdint>
#include <string>
#include <tuple>
#include <algorithm>

#include "hexutils.hpp"

template<size_t length>
class bigint
{
private:
	static const unsigned char bits = 32;
	
	uint32_t* digits;
public:

	bigint()
	{
		digits = new uint32_t[length]{0};
	}

	bigint(const bigint<length>& obj)
	{
		this->digits = obj.digits;
	}
	
	~bigint()
	{
		digits = nullptr;
		delete[] digits;
	}

	static bigint<length> fromConst(const uint64_t c)
	{
		bigint<length> res;

		res.digits[0] = (c & UINT32_MAX);
		res.digits[1] = (c >> 32);

		return res;
	}

	static bigint<length> fromHexString(const std::string& hexString)
	{
		if (!checkHexString(hexString)) return bigint();

		bigint<length> res;
		const size_t hexStringSize = hexString.size();
		size_t i = hexStringSize;

		while(i > 0)
		{
			const size_t digitIndex = (hexStringSize - i) / 8;
			const uint32_t offset = clamp(0, 8, i);
			res.digits[digitIndex] = hexStrToUInt32(hexString.substr(i - offset, offset));
			i -= offset;
		}

		return res;

	}

	bigint longShiftBitsToHigh(const uint32_t n)
	{
		return bigint();
	}
	
	bigint longShiftDigitsToHigh(const uint32_t n)
	{
		return bigint();
	}

	size_t bitLength() const
	{
		return 0;
	}

	std::tuple<bigint<length>, uint8_t> operator+ (const bigint<length>& b)
	{
		uint8_t carry = 0;
		bigint<length> res;
		for (size_t i = 0; i < length; i++)
		{
			uint64_t temp = (uint64_t)digits[i] + (uint64_t)b.digits[i] + (uint64_t)carry;
			res.digits[i] = temp & UINT32_MAX;
			carry = uint8_t(temp >> bits);
		}
		return std::tuple<bigint<length>, uint8_t>(res, carry);
	}

	std::tuple<bigint<length>, uint8_t> operator- (const bigint<length>& b)
	{
		bigint<length> res;
		uint8_t borrow = 0;
		for (size_t i = 0; i < length; i++)
		{
			uint64_t temp = (uint64_t)digits[i] - (uint64_t)b.digits[i] - borrow;
			if (temp >= 0)
			{
				res.digits[i] = temp;
				borrow = 0;
				continue;
			}
			res.digits[i] = temp + ((uint64_t)1 << bits);
			borrow = 1;
		}

		return std::tuple<bigint<length>, uint8_t>(res, borrow);
	}

	bigint<length> operator* (const bigint<length>& b)
	{

	}

	bigint<length> operator/ (const bigint<length>& b)
	{

	}

	friend bool operator== (const bigint<length>& a, const bigint<length>& b)
	{
		size_t i = length - 1;

		while (a.digits[i] == b.digits[i])
		{
			if (i == 0) break;
			i--;
		}

		return i == 0;
	}

	friend bool operator< (const bigint<length>& a, const bigint<length>& b)
	{
		size_t i = length - 1;

		while (a.digits[i] == b.digits[i])
		{
			if (i == 0) break;
			i--;
		}

		return a.digits[i] < b.digits[i];
	}

	friend bool operator> (const bigint<length>& a, const bigint<length>& b)
	{
		return b < a;
	}

	std::string to_string()
	{
		std::string res;
		for (size_t i = length; i > 0; i--)
		{
			res += std::to_string(digits[i - 1]);
			switch (i)
			{
			case 1:
				res += ';';
				break;
			default:
				res += '_';
				break;
			}
		}
		return res;
	}
};

#endif
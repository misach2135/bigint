#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <cstdint>
#include <string>
#include <tuple>
#include <algorithm>

#include "hexutils.hpp"

template<size_t length>
class bigint
{
template<size_t _len>
friend class bigint;

private:
	static const uint8_t bits = 32;
	
	uint32_t* digits;

	uint32_t carry;

	bigint<length> karatsubaMultiply(bigint<length> a, bigint<length> b)
	{

		return bigint<length>();
	}

public:

	bigint()
	{
		digits = new uint32_t[length]{0};
		for (size_t i = 0; i < length; i++)
		{
			digits[i] = 0;
		}
		carry = 0;
	}

	bigint(const bigint<length>& obj) : bigint()
	{
		for (size_t i = 0; i < length; i++)
		{
			digits[i] = obj.digits[i];
		}
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

	uint8_t getCarry() const
	{
		return carry;
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

	static bigint<length> fromHalfLength(const bigint<length / 2>& halfLengthBigInt)
	{
		bigint<length> res;

		for (size_t i = 0; i < length / 2; i++)
		{
			res.digits[i] = halfLengthBigInt.digits[i];
		}

		return res;
	}

	static void longShiftBitsToHigh(bigint<length>& number, uint32_t n)
	{
		if (n >= 32)
		{
			longShiftDigitsToHigh(number, n / 32);
			n = n % 32;
		}
		if (n == 0) return;

		uint32_t t = 0;
		const uint32_t mask = (UINT32_MAX) << (32 - n);
		for (size_t i = length - 1; i > 0; --i)
		{
			t = (number.digits[i - 1] & mask) >> (32 - n);
			number.digits[i] = (number.digits[i] << n) | t;
		}
		number.digits[0] <<= n;
	}

	static void longShiftBitsToDown(bigint<length>& number, uint32_t n)
	{
		if (n == 0) return;

		if (n >= 32)
		{
			longShiftDigitsToDown(number, n / 32);
			n = n % 32;
		}

		const uint32_t mask = (UINT32_MAX) >> (32 - n);
		for (size_t i = 0; i < length; i++)
		{
			uint32_t temp = mask & number.digits[i];
			if (i != 0) number.digits[i - 1] = number.digits[i - 1] | (temp << 31);
			number.digits[i] >>= n;
		}
	}

	
	static void longShiftDigitsToHigh(bigint<length>& number, uint32_t n)
	{
		if (n == 0) return;

		for (size_t i = length; i > 0; i--)
		{
			if (i - 1 < n)
			{
				number.digits[i - 1] = 0;
			}
			else
			{
				number.digits[i - 1] = number.digits[i - 1 - n];
			}
		}
	}
	
	static void longShiftDigitsToDown(bigint<length>& number, uint32_t n)
	{
		if (n == 0)
		{
			return;
		}

		for (size_t i = 0; i < length; i++)
		{
			if (i + n >= length)
			{
				number.digits[i] = 0;
				continue;
			}
			number.digits[i] = number.digits[i + n];
		}

	}

	bigint<length> power(const bigint<length>& n)
	{
		if (n == fromConst(1))
		{
			return *this;
		}

		if (n.isZero())
		{
			return bigint<length>();
		}

		bigint<length> res = fromConst(1);

		for (size_t i = n.bitLength(); i > 0; i--)
		{
			if (n.getIthBit(i - 1))
			{
				res = res * *this;
			}
			if (i - 1 != 0)
			{
				res = res * res;
			}
		}
		return res;
	}

	size_t bitLength() const
	{
		size_t i = length - 1;
		size_t res = 0;
		while (digits[i] == 0)
		{
			i--;
		}
		
		uint32_t n = digits[i];

		while (n != 0)
		{
			n >>= 1;
			res++;
		}
		res += i * 32;
		return res;
	}

	bool getIthBit(size_t i) const
	{
		const uint32_t mask = 1 << (i % 32);
		return (digits[i / 32] >> (i % 32)) & (uint32_t)1;
	}

	void setIthBit(size_t i, bool bit)
	{
		const uint32_t mask = 1 << (i % 32);
		std::cout << "i-th bit of digit" << (digits[i / 32] & mask) << std::endl;
		switch (bit)
		{
		case 0:
			digits[i / 32] = digits[i / 32] & ~mask;
			return;
		case 1:
			digits[i / 32] = digits[i / 32] | mask;
			return;
		}
	}

	bigint<length> operator+ (const bigint<length>& b)
	{
		carry = 0;
		bigint<length> res;
		for (size_t i = 0; i < length; i++)
		{
			uint64_t temp = (uint64_t)digits[i] + (uint64_t)b.digits[i] + (uint64_t)carry;
			res.digits[i] = temp & UINT32_MAX;
			carry = uint8_t(temp >> bits);
		}

		return res;
	}

	bigint<length> operator- (const bigint<length>& b)
	{
		bigint<length> res;
		uint8_t borrow = 0;
		for (size_t i = 0; i < length; i++)
		{
			int64_t temp = (uint64_t)digits[i] - (uint64_t)b.digits[i] - (uint64_t)borrow;
			if (temp >= 0)
			{
				res.digits[i] = temp;
				borrow = 0;
			}
			else
			{
				res.digits[i] = temp + ((uint64_t)1 << bits);
				borrow = 1;
			}
		}
		return res;
	}

	bigint<length> operator* (const bigint<length>& b)
	{
		bigint<length> res;

		for (size_t i = 0; i < length; i++)
		{
			bigint<length> temp = *this * b.digits[i];
			longShiftDigitsToHigh(temp, i);
			res = res + temp;
		}
		return res;
	}
	
	bigint<length> operator* (const uint32_t digit)
	{
		carry = 0;
		bigint<length> res;

		for (size_t i = 0; i < length; i++)
		{
			uint64_t temp = (uint64_t)this->digits[i] * (uint64_t)digit + carry;
			res.digits[i] = temp & UINT32_MAX;
			carry = temp >> bits;
		}

		return res;
	}

	bigint<length> operator/ (const bigint<length>& b)
	{
		const size_t k = b.bitLength();
		bigint<length> r(*this);
		bigint<length> q;

		size_t t = 0;

		while (r >= b)
		{
			t = r.bitLength();
			bigint<length> c(b);
			longShiftBitsToHigh(c, t - k);
			if (r < c)
			{
				t--;
				longShiftBitsToDown(c, 1);
			}
			r = r - c;
			q.setIthBit(t - k, 1);
		}

		return q;
	}

	/*
	bigint<length>& operator=(const bigint<length> obj)
	{
		if (obj == *this)
		{
			return *this;
		}

		bigint<length> res(obj);
		return obj;
	}

	*/

	bool isZero() const
	{
		size_t i = length;
		while (i > 0)
		{
			if (digits[i - 1] != 0) return false;
			i--;
		}
		return true;
	}

	friend bool operator== (const bigint<length>& a, const bigint<length>& b)
	{
		size_t i = length;

		while (i != 0 && a.digits[i - 1] == b.digits[i - 1])
		{
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

	friend bool operator>= (const bigint<length>& a, const bigint<length>& b)
	{
		return !(a < b);
	}

	friend bool operator<= (const bigint<length>& a, const bigint<length>& b)
	{
		return !(a > b);
	}

	std::string toString() const
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

	std::string toHexString() const 
	{
		std::stringstream hexStream;

		hexStream << std::hex;

		const size_t len = bitLength();

		for (size_t i = (len / 32) + 1; i > 0; i--)
		{
			hexStream << digits[i - 1];
		}

		return hexStream.str();
	}

	std::string toBinaryString(bool full = false) const
	{
		std::string res;

		uint32_t last = length;
		while (!full && last != 0 && digits[last - 1] == 0)
		{
			last--;
		}

		for (size_t i = 0; i < last; i++)
		{
			if (digits[i] == 0)
			{
				res += "00000000000000000000000000000000";
				continue;
			}

			res += toReverseBinary(digits[i]);
		}

		std::reverse(res.begin(), res.end());

		return res;
	}

};

#endif
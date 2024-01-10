#include <iostream>

#include "bigint.h"

int main()
{
	using namespace std;
	/*
	bigint<8> i1 = bigint<8>::fromConst(0xFFFFFFFFADBF);
	bigint<8> i2 = bigint<8>::fromConst(0x98573728AAAAA);

	bigint<8> i3 = std::get<0>(i1 + i2);
	bigint<8> i4 = std::get<0>(i1 - i3);

	cout << "i1: " << i1.to_string() << endl;
	cout << "i2: " << i2.to_string() << endl;
	cout << "i1 + i2 = i3: " << i3.to_string() << endl;
	cout << "i3 - i1 = i4: " << i4.to_string() << endl;
	cout << "i1 > i2: " << (i1 > i2) << endl;
	cout << "i1 < i2: " << (i1 < i2) << endl;
	cout << "i1 == i1: " << (i1 == i1) << endl;
	*/

	bigint<5> a = bigint<5>::fromHexString("ff4678274656ababbabaa");
	bigint<5> b = bigint<5>::fromHexString("abbbbbbbdddc");
	cout << "a: " << endl;
	cout << a.bitLength() << endl;
	cout << a.toString() << endl;
	cout << a.toHexString() << endl;
	cout << a.toBinaryString() << endl;

	cout << "b: " << endl;
	cout << b.bitLength() << endl;
	cout << b.toString() << endl;
	cout << b.toHexString() << endl;
	cout << b.toBinaryString() << endl;

	cout << "a * b = " << (a * b).toHexString() << endl;
	// cout << "a * 983 = " << (a * 983).toHexString() << endl;
	// cout << "b * 722 = " << (b * 722).toHexString() << endl;
	cout << "a + b = " << (a + b).toHexString() << endl;
	cout << "a - b = " << (a - b).toHexString() << endl;
	cout << "a < b = " << (a < b) << endl;
	cout << "a > b = " << (a > b) << endl;
	cout << "a <= b = " << (a <= b) << endl;
	cout << "a >= b = " << (a >= b) << endl;
	cout << "a == b = " << (a == b) << endl;
	cout << "a / b = " << (a / b).toHexString() << endl;
	//cout << "a ^ b = " << (a.power(b)).toHexString() << endl;
	/*bigint<5> c(a);
	for (size_t i = 1; i < 10; i++)
	{
		bigint<5>::longShiftDigitsToHigh(c, 1);
		cout << "c <<(digit) " << i << "= " << (c).toHexString() << endl;
		cout << "BitLength: " << (c).bitLength() << endl;

	}
	cout << "\n\n To High:\n";
	bigint<5> d(a);
	for (size_t i = 1; i <= 32; i++)
	{
		bigint<5>::longShiftBitsToHigh(d, 1);
		cout << "d << ";
		if (i / 10 == 0)
		{
			cout << "0";
		}
		cout << i;
		cout << "= " << (d).toBinaryString() << endl;
		cout << "BitLength: " << (d).bitLength() << endl;

	}
	
	cout << "\n\n To down:\n";

	for (size_t i = 1; i <= 32; i++)
	{
		bigint<5>::longShiftBitsToDown(d, 1);
		cout << "d >> ";
		if (i / 10 == 0)
		{
			cout << "0";
		}
		cout << i;
		cout << "= " << (d).toBinaryString() << endl;
		cout << "BitLength: " << (d).bitLength() << endl;

	}
	*/
	return 0;
}
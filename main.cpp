#include <iostream>

#include "bigint.h"

int main()
{
	using namespace std;
	
	bigint<5> i1 = bigint<5>::fromHexString("1a3f");
	bigint<5> i2 = bigint<5>::fromHexString("1a3f");

	cout << i1.toHexString() << endl;
	cout << i1.toBinaryString() << endl;
	cout << i1.bitLength() << endl;
	cout << endl;
	cout << endl;
	cout << i2.toHexString() << endl;
	cout << i2.toBinaryString() << endl;
	cout << i2.bitLength() << endl;

	cout << "Square: " << endl;
	cout << (i1 * i2).toBinaryString() << endl;
	
	cout << "Shift << 1" << endl;
	bigint<5> c(i1);
	c.longShiftDigitsToHigh(c, 4);
	cout << c.toHexString() << endl;

	return 0;
}
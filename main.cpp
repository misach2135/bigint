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

	bigint<32> iFromHex = bigint<32>::fromHexString("abababbbfff9348");
	cout << iFromHex.to_string() << endl;

	return 0;
}
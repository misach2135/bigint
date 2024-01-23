#include <iostream>
#include <chrono>
#include <cassert>

#include "bigint.hpp"

const size_t len = 128;

bigint<len> a = bigint<len>::fromHexString("658EC5E5D8F126D692936C196BC1BE68FDBC7483D7F1035C8E636C36ED5D4D0F0F69A0FA8158F4D0967E3EBD23AA4081F14540FB4F4724140E38AB2A40D33E807028B2F40B1E5362C392348D7CD81DDE9EC6A79E1F4ABB8B706EA0D63D30F0663A2CA1FF673D8889BC315853FCA663A2C05F46C87657F0FEA4EC2AAFE8BBF3AC");
bigint<len> b = bigint<len>::fromHexString("5BFFD2AD88C901A224CABA35BA09C26AE6BE9C06DAE976A0FC91B7E6F5076559813CB94D2B33E86C9BF1AFABC4598E769FD3E7C27BC45BBEAB5E78CE48FABE89EF514FF65C64DA6E6858A91600DE5B4091B219B88FF502FD166EA1EF805E37BC0695D17348823898C0A7BFE217D7980CA93B724B2AECEC6C4F0165E9B30002E2");
bigint<len> c = bigint<len>::fromHexString("F5AA1BD307EEDF96DB133A218AA605A0EDB6DE4FA9D43D100CD75990B3C9B72347FF83796C2F886B4A58F312B8BDBDBCAF500790EEE9ADD7165837032D2BD268E9A73CB50DCA7A065ABB515A18F8783C9F1BDAA5400A2B2F06CC42A2B38F41599D5BAB219AAFF407F6C283D479DE944F8D039233709E21E30AA380B98026AC33");

void testMultiplyProperties()
{
	using namespace std;

	auto start = std::chrono::system_clock::now();
	
	bigint<len> t1 = (a + b) * c;
	bigint<len> t2 = c * (a + b);
	bigint<len> t3 = a * c + b * c;

	assert(t1 == t2);
	assert(t2 == t3);
	assert(t1 == t3);

	auto end = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	cout << "(a + b) * c = c * (a + b) = ca + cb: " << elapsed.count() << "ms. \n";

	start = std::chrono::system_clock::now();

	bigint<len> t4 = a * bigint<len>::fromConst(4134);
	bigint<len> t5 = a;
	for (int i = 0; i < 4133; i++)
	{
		t5 = t5 + a;
	}

	assert(t4 == t5);

	end = std::chrono::system_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	cout << "a * n = a + a + a.. + a: " << elapsed.count() << "ms. \n";
}

void testDivide()
{
	using namespace std;

	auto start = std::chrono::system_clock::now();

	auto t1 = a.longDivision(a, b);

	cout << "a / b: " << t1.first.toHexString() << endl;
	cout << "a % b: " << t1.second.toHexString() << endl;


	auto end = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	cout << "Divide and Modulo operation: " << elapsed.count() << "ms. \n";
	
	assert(t1.first == bigint<len>::fromHexString("7cb70e871d43cb173ff925eadf8b81dc1253d6b9ee6"));
	assert(t1.second == bigint<len>::fromHexString("6ac3e334cf6557328430c0286ce87e5cf9ee9e78472bc"));
}

void testMultiply()
{
	using namespace std;

	auto start = std::chrono::system_clock::now();

	auto t1 = a * b;

	cout << "a * b: " << t1.toHexString() << endl;

	auto end = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	cout << "Multiply operation: " << elapsed.count() << "ms. \n";
	
	assert(t1 == bigint<len>::fromHexString("9f0225fc073713cca27a7e68fa0d9595841bd1cd60baa86893089e69a4f5c09ed98b316a7b29223439ca3fc6a9666d0c973291291e245b22375ce5939e1867fcdf0ca"));
}

void testGCD()
{
	using namespace std;

	auto start = std::chrono::system_clock::now();

	auto t1 = bigint<len>::gcd(a, b);
	auto t2 = bigint<len>::gcd(a * c, b * c);

	assert(t1 == bigint<len>::fromConst(1));
	assert(t2 == c);

	auto end = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	cout << "GCD: " << elapsed.count() << "ms. \n";
	cout << "GCD = " << t2.toHexString() << endl;
}

void testLCM()
{
	using namespace std;

	auto start = std::chrono::system_clock::now();

	auto t1 = bigint<len>::lcm(a, b);

	assert(t1 == bigint<len>::fromHexString("9f0225fc073713cca27a7e68fa0d9595841bd1cd60baa86893089e69a4f5c09ed98b316a7b29223439ca3fc6a9666d0c973291291e245b22375ce5939e1867fcdf0ca"));

	auto end = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	cout << "LCM: " << elapsed.count() << "ms. \n";
	cout << "LCM = " << t1.toHexString() << endl;
}

void testModuloOperations()
{
	using namespace std;

	auto start = std::chrono::system_clock::now();
	bigint<len> t1 = a.addMod(b, c);
	auto end = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	cout << "Addition(mod c): " << elapsed.count() << "ms. \n";

	start = std::chrono::system_clock::now();
	bigint<len> t2 = a.subMod(b, c);
	end = std::chrono::system_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	cout << "Substraction(mod c): " << elapsed.count() << "ms. \n";

	start = std::chrono::system_clock::now();
	bigint<len> t3 = a.multiplyMod(b, c);
	end = std::chrono::system_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	cout << "Multiply(mod c): " << elapsed.count() << "ms. \n";
	
	start = std::chrono::system_clock::now();
	bigint<len> t4 = a.powerMod(b, c);
	end = std::chrono::system_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	cout << "Power(mod c): " << elapsed.count() << "ms. \n";
	
	assert(t1 == bigint<len>::fromHexString("7f745326e7f025efeffc8a3e35419"));
	assert(t2 == bigint<len>::fromHexString("2901a9089d7a81b8cef95e2adebff3"));
	assert(t3 == bigint<len>::fromHexString("453d537b1af02ff1b2da2ef76517ea"));
	assert(t4 == bigint<len>::fromHexString("11ff0970f521fc2d462a3d5ea681b0"));
}

void testBarretReduction()
{
	using namespace std;

	bigint<len> tA = bigint<len>::fromHexString("3fa55affaa");
	bigint<len> tMod = bigint<len>::fromHexString("ab9af");

	cout << "tA: " << tA.toHexString() << endl;
	cout << "tMod: " << tMod.toHexString() << endl;
	cout << "tMod^2: " << tMod.power(bigint<len>::fromConst(2)).toHexString() << endl;

	cout << (tA % tMod).toHexString() << endl;
	cout << (tA.barretReduction(tMod)).toHexString() << endl;
}

int main()
{
	using namespace std;
	cout << "A(hex) = " << a.toHexString() << endl;
	cout << "A(bin) = " << a.toBinaryString() << endl;
	cout << "A(raw) = " << a.toString() << endl;
	cout << "\n\n";

	cout << "B(hex) = " << b.toHexString() << endl;
	cout << "B(bin) = " << b.toBinaryString() << endl;
	cout << "B(raw) = " << b.toString() << endl;
	cout << "\n\n";

	cout << "C(hex) = " << c.toHexString() << endl;
	cout << "C(bin) = " << c.toBinaryString() << endl;
	cout << "C(raw) = " << c.toString() << endl;
	cout << "\n\n";
	/*
	testMultiply();
	testDivide();
	testGCD();
	testLCM();
	testModuloOperations();
	*/

	cout << "A * B = " << a.multiplyMod(b, c).toHexString() << endl;
	cout << "A + B = " << a.addMod(b, c).toHexString() << endl;
	cout << "A - B = " << (a.subMod(b, c)).toHexString() << endl;
	cout << "A % B = " << (a % b).toHexString() << endl;
	cout << "A ^ B = " << a.powerMod(b, c).toHexString() << endl;
	cout << "WIP Tests: \n\n";

	// testBarretReduction();

	return 0;
}
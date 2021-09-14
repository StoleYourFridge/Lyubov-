#include <iostream>

using namespace std;

class NaturalFraction
{
private:
	int numerator, denominator;
	bool numeratorSet, denominatorSet; // bool values are required to check if it is allowed to reduce a fraction after setting some value
	void reduce();
public:
	NaturalFraction();
	NaturalFraction(int num, int den);
	NaturalFraction(const NaturalFraction& currFraction);

	int getNumerator();
	int getDenominator();
	void setNumerator(int newNum);
	void setDenominator(int newDen);
	int getIntegerPart();
	double toDouble();

	NaturalFraction operator+(const NaturalFraction& term);
	NaturalFraction operator+(int term);
	NaturalFraction operator-(int term);
	NaturalFraction operator*(const NaturalFraction& m);
	NaturalFraction operator*(int m);
	NaturalFraction operator/(const NaturalFraction& m);
	NaturalFraction operator/(int term);
	
	void operator+=(const NaturalFraction& term);
	void operator+=(int term);
	void operator-=(int term);
	void operator*=(const NaturalFraction& m);
	void operator*=(int m);
	void operator/=(const NaturalFraction& m);
	void operator/=(int term);

	void operator=(const NaturalFraction& term);

	bool operator==(const NaturalFraction& term);
	bool operator!=(const NaturalFraction& term);

	friend istream& operator>>(istream& input, NaturalFraction& fr);
	friend ostream& operator<<(ostream& input, NaturalFraction& fr);
};

void tests();
void printTestResult(bool result, int* counter);

bool test1();																						// test 1: testing the ability to take the numerator of a fraction
bool test2();																						// test 2: testing the ability to take the denominator of a fraction
bool test3_5(NaturalFraction* fr, int expected);													// tests 3-5: testing the ability to take the integer part of a fraction
bool test6_10(NaturalFraction* fr, int expectedNum, int expectedDen);								// tests 6-10: testing the ability to reduce a fraction
bool test11_15(NaturalFraction* fr, double expected);												// tests 11-15: testing the ability to convert a fraction to double
bool test16_20(NaturalFraction* fr, int expectedNum, int expectedDen);								// tests 16-20: testing the ability to copy a fraction
bool test21_24(NaturalFraction* fr1, NaturalFraction* fr2, bool expected);							// tests 21-24: testing the ability to check if two fractions are equal 
bool test25_28(NaturalFraction* fr1, NaturalFraction* fr2, bool expected);							// tests 25-28: testing the ability to check if two fractions are not equal
bool test29_33(NaturalFraction* fr1, NaturalFraction* fr2, NaturalFraction* expected);				// tests 29-33: testing the ability to add two fractions (+)
bool test34_38(NaturalFraction* fr1, NaturalFraction* fr2, NaturalFraction* expected);				// tests 34-38: testing the ability to add two fractions (+=)
bool test39_41(NaturalFraction* fr, int term, NaturalFraction* expected);							// tests 39-41: testing the ability to add a number to a fraction (+)
bool test42_44(NaturalFraction* fr, int term, NaturalFraction* expected);							// tests 42-44: testing the ability to add a number to a fraction (+=)
bool test45_49(NaturalFraction* fr1, NaturalFraction* fr2, NaturalFraction* expected);				// tests 45-49: testing the ability to subtract a fraction from a fraction (-)
bool test50_54(NaturalFraction* fr1, NaturalFraction* fr2, NaturalFraction* expected);				// tests 50-54: testing the ability to subtract a fraction from a fraction (-=)
bool test55_57(NaturalFraction* fr, int term, NaturalFraction* expected);							// tests 55-57: testing the ability to subtract a number from a fraction (-)
bool test58_60(NaturalFraction* fr, int term, NaturalFraction* expected);							// tests 58-60: testing the ability to subtract a number from a fraction (-=)
bool test61_63(NaturalFraction* fr1, NaturalFraction* fr2, NaturalFraction* expected);				// tests 61-63: testing the ability to multiply two fractions (*)
bool test64_66(NaturalFraction* fr1, NaturalFraction* fr2, NaturalFraction* expected);				// tests 64-66: testing the ability to multiply two fractions (*=)
bool test67_69(NaturalFraction* fr, int term, NaturalFraction* expected);							// tests 67-69 (nice): testing the ability to multiply a fraction by a number (*)
bool test70_72(NaturalFraction* fr, int term, NaturalFraction* expected);							// tests 70-72: testing the ability to multiply a fraction by a number (*=)
bool test73_75(NaturalFraction* fr1, NaturalFraction* fr2, NaturalFraction* expected);				// tests 73-75: testing the ability to divide a fraction by a fraction (/)
bool test76_78(NaturalFraction* fr1, NaturalFraction* fr2, NaturalFraction* expected);				// tests 76-78: testing the ability to divide a fraction by a fraction (/=)
bool test79_81(NaturalFraction* fr, int term, NaturalFraction* expected);							// tests 79-81: testing the ability to divide a fraction by a number (/)
bool test82_84(NaturalFraction* fr, int term, NaturalFraction* expected);							// tests 82-84: testing the ability to divide a fraction by a number (/=)
bool test85_86(NaturalFraction* fr, NaturalFraction* expected);										// tests 85-86: testing the preincrement operator (++fr)
bool test87_88(NaturalFraction* fr, NaturalFraction* expected);										// tests 87-88: testing the postincrement operator (fr++)
bool test89_90(NaturalFraction* fr, NaturalFraction* expected);										// tests 89-90: testing the predecrement operator (--fr)
bool test91_92(NaturalFraction* fr, NaturalFraction* expected);										// tests 91-92: testing the postdecrement operator (fr--)
bool test93_94(NaturalFraction* fr1, NaturalFraction* fr2, bool expected);							// test 93-94: testing the ability to compare two fractions (>)
bool test95_96(NaturalFraction* fr1, NaturalFraction* fr2, bool expected);							// test 95-96: testing the ability to compare two fractions (>=)
bool test97_98(NaturalFraction* fr1, NaturalFraction* fr2, bool expected);							// test 97-98: testing the ability to compare two fractions (<)
bool test99_100(NaturalFraction* fr1, NaturalFraction* fr2, bool expected);							// test 99-100: testing the ability to compare two fractions (<=)
bool test101_102(NaturalFraction* fr, int number, bool expected);									// test 101-102: testing the ability to compare a fraction and a number (>)
bool test103_104(NaturalFraction* fr, int number, bool expected);									// test 103-104: testing the ability to compare a fraction and a number (>=)
bool test105_106(NaturalFraction* fr, int number, bool expected);									// test 105-106: testing the ability to compare a fraction and a number (<)
bool test107_108(NaturalFraction* fr, int number, bool expected);									// test 107-108: testing the ability to compare a fraction and a number (<=)
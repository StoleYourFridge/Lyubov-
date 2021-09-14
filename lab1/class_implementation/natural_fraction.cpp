#define _CRT_SECURE_NO_WARNINGS

#include "natural_fraction.h"
#include <iostream>

using namespace std;

NaturalFraction::NaturalFraction() // default constructor
{
	setNumerator(1); // a 1/1 fraction will be created if no arguments specified
	setDenominator(1);
}
NaturalFraction::NaturalFraction(int num, int den) // a constructor that takes the numerator and the denominator as arguments
{
	setNumerator(num);
	setDenominator(den);
}
NaturalFraction::NaturalFraction(NaturalFraction& currFraction) // copy constructor
{
	numerator = currFraction.numerator;
	denominator = currFraction.denominator;
} 

int NaturalFraction::getNumerator() { return numerator; } // returns the numerator of a fraction
int NaturalFraction::getDenominator() { return denominator; } // returns the denominator of a fraction
void NaturalFraction::setNumerator(int newNum) //  sets the numerator of a fraction
{ 
	numerator = newNum; 
	numeratorSet = true;
	reduce();
} 
void NaturalFraction::setDenominator(int newDen) // sets the denominator of a fraction
{ 
	denominator = newDen; 
	denominatorSet = true;
	reduce();
} 
int NaturalFraction::getIntegerPart() { return numerator / denominator; } // returns the integer part of a fraction
void NaturalFraction::reduce() // reduces the fraction
{ 
	if (!numeratorSet || !denominatorSet) return; // there's no need for reduction if the fraction isn't assigned all values yet
	int less = (numerator < denominator) ? numerator : denominator; // the cycle that will reduce the numerator and the denominator will only go as far as the least of the numbers that make up the fraction
	for (int currdivisor = 2; currdivisor <= less; currdivisor++) // there's no need to check if 1 is a common divisor, because it always will be, and reduction by 1 doesn't change the fraction
	{
		if (numerator % currdivisor == 0 && denominator % currdivisor == 0)
		{
			numerator /= currdivisor; // if the numerator and the denominator are both divisible by some number, they are both divided by this number
			denominator /= currdivisor;
			currdivisor--; // we need to return one number back in order to account for possible bigger than one powers of primes; for example, 8/16 should be reduced to 1/2, not 4/8
		}
	}
} 
double NaturalFraction::toDouble() // converts the fraction to double
{
	double numeratorDouble = numerator * 1.0;
	return numeratorDouble / denominator;
}

NaturalFraction NaturalFraction::operator+(const NaturalFraction& term) // adds two fractions, returns their sum
{
	NaturalFraction result;
	result.setDenominator(term.denominator * denominator);
	result.setNumerator(numerator * term.denominator + term.numerator * denominator);
	return result;
}
NaturalFraction NaturalFraction::operator-(const NaturalFraction& term)
{
	NaturalFraction result;
	result.setDenominator(term.denominator * denominator);
	result.setNumerator(numerator * term.denominator - term.numerator * denominator);
	return result;
}
NaturalFraction NaturalFraction::operator*(const NaturalFraction& m) // multiplies two fractions, returns their product
{
	NaturalFraction multiplication;
	multiplication.setDenominator(m.denominator * denominator);
	multiplication.setNumerator(m.numerator * numerator);
	return multiplication;
}
NaturalFraction NaturalFraction::operator/(const NaturalFraction& m) // divides a fraction by a fraction, returns their quotient
{
	NaturalFraction division;
	division.setDenominator(denominator * m.numerator);
	division.setNumerator(numerator * m.denominator);
	return division;
}

NaturalFraction NaturalFraction::operator+(int term) // adds a number to a fraction, returns their sum
{
	NaturalFraction result;
	result.setDenominator(denominator);
	result.setNumerator(numerator + term * denominator);
	return result;
}
NaturalFraction NaturalFraction::operator-(int term) // subtracts a number from a fraction, returns their difference
{
	NaturalFraction result;
	result.setDenominator(denominator);
	result.setNumerator(numerator - term * denominator);
	return result;
}
NaturalFraction NaturalFraction::operator*(int m) // multiplies a fraction by a number, returns their product
{
	NaturalFraction multiplication;
	multiplication.setNumerator(m * numerator);
	multiplication.setDenominator(denominator);
	return multiplication;
}
NaturalFraction NaturalFraction::operator/(int term) // divides a fraction by a number, returns their quotient
{
	NaturalFraction result;
	result.setNumerator(numerator);
	result.setDenominator(denominator * term); // we multiply the denominator rather than divide the numerator in order to account for cases when the numerator isn't divisible by the number we fed into the function, for example, 1/3 : 3 should be 1/9, not (1/3)/3
	return result;
}

void NaturalFraction::operator+=(const NaturalFraction& term) // adds two fractions with assignment
{
	int tempdenominator = denominator;
	denominator = term.denominator * denominator;
	numerator = numerator * term.denominator + term.numerator * tempdenominator;
	reduce();
}
void NaturalFraction::operator-=(const NaturalFraction& term)
{	
	int tempdenominator = denominator;
	denominator = term.denominator * denominator;
	numerator = numerator * term.denominator - term.numerator * tempdenominator;
	reduce();
}
void NaturalFraction::operator*=(const NaturalFraction& m) // multiplies two fractions with assignment
{
	setDenominator(m.denominator * denominator);
	setNumerator(m.numerator * numerator);
}
void NaturalFraction::operator/=(const NaturalFraction& m) // divides a fraction by a fraction with assignment
{
	setDenominator(denominator * m.numerator);
	setNumerator(numerator * m.denominator);
}

void NaturalFraction::operator+=(int term) // adds a number to a fraction with assignment
{
	setNumerator(numerator + term * denominator);
} 
void NaturalFraction::operator-=(int term) // subtracts a number from a fraction with assignment
{
	setNumerator(numerator - term * denominator);
}
void NaturalFraction::operator/=(int term) // divides a fraction by a number with assignment
{
	setDenominator(denominator * term);
}
void NaturalFraction::operator*=(int m)
{
	setNumerator(m * numerator);
}

void NaturalFraction::operator++()
{
	setNumerator(numerator + denominator);
}

void NaturalFraction::operator--()
{
	setNumerator(numerator - denominator);
}

void NaturalFraction::operator++(int)
{
	setNumerator(numerator + denominator);
}

void NaturalFraction::operator--(int)
{
	setNumerator(numerator - denominator);
}



bool NaturalFraction::operator==(const NaturalFraction& term) // checks if two fractions are equal
{
	if (numerator == term.numerator && denominator == term.denominator) return true;
	else return false;
}
bool NaturalFraction::operator!=(const NaturalFraction& term) // checks if two fractions are not equal
{
	if (numerator != term.numerator || denominator != term.denominator) return true;
	else return false;
}

bool NaturalFraction::operator>=(const NaturalFraction& term)
{
	if ((*(this) - term).getNumerator() >= 0) return true;
	else return false;
}

bool NaturalFraction::operator<=(const NaturalFraction& term)
{
	if ((*(this) - term).getNumerator() <= 0) return true;
	else return false;
}

bool NaturalFraction::operator<(const NaturalFraction& term)
{
	if ((*(this) - term).getNumerator() < 0) return true;
	else return false;
}

bool NaturalFraction::operator>(const NaturalFraction& term)
{
	if ((*(this) - term).getNumerator() > 0) return true;
	else return false;
}

bool NaturalFraction::operator<=(int term)
{
	if ((*(this) - term).getNumerator() <= 0) return true;
	else return false;
}

bool NaturalFraction::operator>=(int term)
{
	if ((*(this) - term).getNumerator() >= 0) return true;
	else return false;
}

bool NaturalFraction::operator<(int term)
{
	if ((*(this) - term).getNumerator() < 0) return true;
	else return false;
}

bool NaturalFraction::operator>(int term)
{
	if ((*(this) - term).getNumerator() > 0) return true;
	else return false;
}

istream& operator>>(istream& input, NaturalFraction& fr)
{
	input >> fr.numerator >> fr.denominator;
	fr.reduce();
	return input;
}
ostream& operator<<(ostream& output, NaturalFraction& fr)
{
	output << fr.numerator << "/" << fr.denominator;
	return output;
}

void tests()
{
	int testsPassed = 0;

	printf("\n----taking the numerator and the denominator----\n\n");
	printTestResult(test1(), &testsPassed);
	printTestResult(test2(), &testsPassed);

	printf("\n----taking the integer part----\n\n");
	printTestResult(test3_5(new NaturalFraction(3,5), 0), &testsPassed);
	printTestResult(test3_5(new NaturalFraction(13,6), 2), &testsPassed);
	printTestResult(test3_5(new NaturalFraction(73,15), 4), &testsPassed);

	printf("\n----reducing a fraction----\n\n");
	printTestResult(test6_10(new NaturalFraction(6,8), 3, 4), &testsPassed);
	printTestResult(test6_10(new NaturalFraction(30,15), 2, 1), &testsPassed);
	printTestResult(test6_10(new NaturalFraction(8,40), 1, 5), &testsPassed);
	printTestResult(test6_10(new NaturalFraction(10395,46080), 231, 1024), &testsPassed);
	printTestResult(test6_10(new NaturalFraction(3628800, 6302920), 90720, 157573), &testsPassed);

	printf("\n----converting a fraction to double----\n\n");
	printTestResult(test11_15(new NaturalFraction(1,2), 1/2.0), &testsPassed);
	printTestResult(test11_15(new NaturalFraction(4,5), 4/5.0), &testsPassed);
	printTestResult(test11_15(new NaturalFraction(18,7), 18/7.0), &testsPassed);
	printTestResult(test11_15(new NaturalFraction(1563,124), 1563/124.0), &testsPassed);
	printTestResult(test11_15(new NaturalFraction(52137,389257), 52137/389257.0), &testsPassed);

	printf("\n----copying a fraction----\n\n");
	printTestResult(test16_20(new NaturalFraction(3,5), 3, 5), &testsPassed);
	printTestResult(test16_20(new NaturalFraction(5,8), 5, 8), &testsPassed);
	printTestResult(test16_20(new NaturalFraction(15,7), 15, 7), &testsPassed);
	printTestResult(test16_20(new NaturalFraction(346,21), 346, 21), &testsPassed);
	printTestResult(test16_20(new NaturalFraction(1,2351), 1, 2351), &testsPassed);

	printf("\n----checking if two fractions are equal----\n\n");
	printTestResult(test21_24(new NaturalFraction(2,3), new NaturalFraction(2,3), true), &testsPassed);
	printTestResult(test21_24(new NaturalFraction(10,13), new NaturalFraction(11,13), false), &testsPassed);
	printTestResult(test21_24(new NaturalFraction(101,21), new NaturalFraction(101,21), true), &testsPassed);
	printTestResult(test21_24(new NaturalFraction(461309,12498), new NaturalFraction(461309,12499), false), &testsPassed);

	printf("\n----checking if two fractions are not equal----\n\n");
	printTestResult(test25_28(new NaturalFraction(5,8), new NaturalFraction(5,8), false), &testsPassed);
	printTestResult(test25_28(new NaturalFraction(10,3), new NaturalFraction(11,3), true), &testsPassed);
	printTestResult(test25_28(new NaturalFraction(8041,1023), new NaturalFraction(8041,1023), false), &testsPassed);
	printTestResult(test25_28(new NaturalFraction(135087,491208), new NaturalFraction(135087,491207), true), &testsPassed);

	printf("\n----adding two fractions (+)----\n\n");
	printTestResult(test29_33(new NaturalFraction(1,3), new NaturalFraction(1,3), new NaturalFraction(2,3)), &testsPassed);
	printTestResult(test29_33(new NaturalFraction(5,8), new NaturalFraction(4,2), new NaturalFraction(21,8)), &testsPassed);
	printTestResult(test29_33(new NaturalFraction(12,11), new NaturalFraction(8,31), new NaturalFraction(460,341)), &testsPassed);
	printTestResult(test29_33(new NaturalFraction(29,100), new NaturalFraction(90,17), new NaturalFraction(9493,1700)), &testsPassed);
	printTestResult(test29_33(new NaturalFraction(37821,1274), new NaturalFraction(6437,5178), new NaturalFraction(7287067,235599)), &testsPassed);

	printf("\n----adding two fractions (+=)----\n\n");
	printTestResult(test34_38(new NaturalFraction(1, 3), new NaturalFraction(1, 3), new NaturalFraction(2, 3)), &testsPassed);
	printTestResult(test34_38(new NaturalFraction(5, 8), new NaturalFraction(4, 2), new NaturalFraction(21, 8)), &testsPassed);
	printTestResult(test34_38(new NaturalFraction(12, 11), new NaturalFraction(8, 31), new NaturalFraction(460, 341)), &testsPassed);
	printTestResult(test34_38(new NaturalFraction(29, 100), new NaturalFraction(90, 17), new NaturalFraction(9493, 1700)), &testsPassed);
	printTestResult(test34_38(new NaturalFraction(37821, 1274), new NaturalFraction(6437, 5178), new NaturalFraction(7287067, 235599)), &testsPassed);

	printf("\n----adding a number to a fraction (+)----\n\n");
	printTestResult(test39_41(new NaturalFraction(1,3), 2, new NaturalFraction(7,3)), &testsPassed);
	printTestResult(test39_41(new NaturalFraction(29,11), 19, new NaturalFraction(238,11)), &testsPassed);
	printTestResult(test39_41(new NaturalFraction(139,23), 123, new NaturalFraction(2968,23)), &testsPassed);

	printf("\n----adding a number to a fraction (+=)----\n\n");
	printTestResult(test42_44(new NaturalFraction(1, 3), 2, new NaturalFraction(7, 3)), &testsPassed);
	printTestResult(test42_44(new NaturalFraction(29, 11), 19, new NaturalFraction(238, 11)), &testsPassed);
	printTestResult(test42_44(new NaturalFraction(139, 23), 123, new NaturalFraction(2968, 23)), &testsPassed);

	printf("\n----subtracting a fraction from a fraction (-)----\n\n");
	printTestResult(test45_49(new NaturalFraction(4,7), new NaturalFraction(1,7), new NaturalFraction(3,7)), &testsPassed);
	printTestResult(test45_49(new NaturalFraction(11,13), new NaturalFraction(2,13), new NaturalFraction(9,13)), &testsPassed);
	printTestResult(test45_49(new NaturalFraction(16,7), new NaturalFraction(2,9), new NaturalFraction(130,63)), &testsPassed);
	printTestResult(test45_49(new NaturalFraction(78,17), new NaturalFraction(13,9), new NaturalFraction(481,153)), &testsPassed);
	printTestResult(test45_49(new NaturalFraction(139235,19), new NaturalFraction(89,1294), new NaturalFraction(180168399,24586)), &testsPassed);

	printf("\n----subtracting a fraction from a fraction (-=)----\n\n");
	printTestResult(test50_54(new NaturalFraction(4,7), new NaturalFraction(1,7), new NaturalFraction(3,7)), &testsPassed);
	printTestResult(test50_54(new NaturalFraction(11,13), new NaturalFraction(2,13), new NaturalFraction(9,13)), &testsPassed);
	printTestResult(test50_54(new NaturalFraction(16,7), new NaturalFraction(2,9), new NaturalFraction(130,63)), &testsPassed);
	printTestResult(test50_54(new NaturalFraction(78,17), new NaturalFraction(13,9), new NaturalFraction(481,153)), &testsPassed);
	printTestResult(test50_54(new NaturalFraction(139235,19), new NaturalFraction(89,1294), new NaturalFraction(180168399,24586)), &testsPassed);

	printf("\n----subtracting a number from a fraction (-)----\n\n");
	printTestResult(test55_57(new NaturalFraction(14,9), 1, new NaturalFraction(5,9)), &testsPassed);
	printTestResult(test55_57(new NaturalFraction(78,15), 3, new NaturalFraction(33,15)), &testsPassed);
	printTestResult(test55_57(new NaturalFraction(1259,7), 42, new NaturalFraction(965,7)), &testsPassed);

	printf("\n----subtracting a number from a fraction (-=)----\n\n");
	printTestResult(test58_60(new NaturalFraction(14, 9), 1, new NaturalFraction(5, 9)), &testsPassed);
	printTestResult(test58_60(new NaturalFraction(78, 15), 3, new NaturalFraction(33, 15)), &testsPassed);
	printTestResult(test58_60(new NaturalFraction(1259, 7), 42, new NaturalFraction(965, 7)), &testsPassed);

	printf("\n----multiplying a fraction by a fraction (*)----\n\n");
	printTestResult(test61_63(new NaturalFraction(2,5), new NaturalFraction(14,3), new NaturalFraction(28,15)), &testsPassed);
	printTestResult(test61_63(new NaturalFraction(29,5), new NaturalFraction(12,11), new NaturalFraction(348,55)), &testsPassed);
	printTestResult(test61_63(new NaturalFraction(1298,413), new NaturalFraction(234,2358), new NaturalFraction(303732,973854)), &testsPassed);

	printf("\n----multiplying a fraction by a fraction (*=)----\n\n");
	printTestResult(test64_66(new NaturalFraction(2,5), new NaturalFraction(14,3), new NaturalFraction(28,15)), &testsPassed);
	printTestResult(test64_66(new NaturalFraction(29,5), new NaturalFraction(12,11), new NaturalFraction(348,55)), &testsPassed);
	printTestResult(test64_66(new NaturalFraction(1298,413), new NaturalFraction(234,2358), new NaturalFraction(303732,973854)), &testsPassed);

	printf("\n----multiplying a fraction by a number (*)----\n\n");
	printTestResult(test67_69(new NaturalFraction(2,3), 4, new NaturalFraction(8,3)), &testsPassed);
	printTestResult(test67_69(new NaturalFraction(10,7), 7, new NaturalFraction(10,1)), &testsPassed);
	printTestResult(test67_69(new NaturalFraction(265,11), 22, new NaturalFraction(530,1)), &testsPassed);

	printf("\n----multiplying a fraction by a number (*=)----\n\n");
	printTestResult(test70_72(new NaturalFraction(2,3), 4, new NaturalFraction(8,3)), &testsPassed);
	printTestResult(test70_72(new NaturalFraction(10,7), 7, new NaturalFraction(10,1)), &testsPassed);
	printTestResult(test70_72(new NaturalFraction(265,11), 22, new NaturalFraction(530,1)), &testsPassed);

	printf("\n----dividing a fraction by a fraction (/)----\n\n");
	printTestResult(test73_75(new NaturalFraction(16,7), new NaturalFraction(7,2), new NaturalFraction(32,49)), &testsPassed);
	printTestResult(test73_75(new NaturalFraction(29,5), new NaturalFraction(1,25), new NaturalFraction(145,1)), &testsPassed);
	printTestResult(test73_75(new NaturalFraction(1298,413), new NaturalFraction(234,2358), new NaturalFraction(3060684,96642)), &testsPassed);

	printf("\n----dividing a fraction by a fraction (/=)----\n\n");
	printTestResult(test76_78(new NaturalFraction(16,7), new NaturalFraction(7,2), new NaturalFraction(32,49)), &testsPassed);
	printTestResult(test76_78(new NaturalFraction(29,5), new NaturalFraction(1,25), new NaturalFraction(145,1)), &testsPassed);
	printTestResult(test76_78(new NaturalFraction(1298,413), new NaturalFraction(234,2358), new NaturalFraction(3060684,96642)), &testsPassed);

	printf("\n----dividing a fraction by a number (/)----\n\n");
	printTestResult(test79_81(new NaturalFraction(8,3), 4, new NaturalFraction(2,3)), &testsPassed);
	printTestResult(test79_81(new NaturalFraction(10,7), 10, new NaturalFraction(1,7)), &testsPassed);
	printTestResult(test79_81(new NaturalFraction(99,11), 9, new NaturalFraction(1,1)), &testsPassed);

	printf("\n----dividing a fraction by a number (/=)----\n\n");
	printTestResult(test82_84(new NaturalFraction(8,3), 4, new NaturalFraction(2,3)), &testsPassed);
	printTestResult(test82_84(new NaturalFraction(10,7), 10, new NaturalFraction(1,7)), &testsPassed);
	printTestResult(test82_84(new NaturalFraction(99,11), 9, new NaturalFraction(1,1)), &testsPassed);

	printf("\n----preincrement operator (++fr)----\n\n");
	printTestResult(test85_86(new NaturalFraction(5,8), new NaturalFraction(13,8)), &testsPassed);
	printTestResult(test85_86(new NaturalFraction(113,200), new NaturalFraction(313,200)), &testsPassed);

	printf("\n----postincrement operator (fr++)----\n\n");
	printTestResult(test87_88(new NaturalFraction(5,8), new NaturalFraction(13,8)), &testsPassed);
	printTestResult(test87_88(new NaturalFraction(113,200), new NaturalFraction(313,200)), &testsPassed);

	printf("\n----predecrement operator (--fr)----\n\n");
	printTestResult(test89_90(new NaturalFraction(79,13), new NaturalFraction(66,13)), &testsPassed);
	printTestResult(test89_90(new NaturalFraction(201,31), new NaturalFraction(170,31)), &testsPassed);

	printf("\n----postdecrement operator (fr--)----\n\n");
	printTestResult(test91_92(new NaturalFraction(79, 13), new NaturalFraction(66, 13)), &testsPassed);
	printTestResult(test91_92(new NaturalFraction(201, 31), new NaturalFraction(170, 31)), &testsPassed);

	printf("\n----comparing two fractions (>)----\n\n");
	printTestResult(test93_94(new NaturalFraction(2,3), new NaturalFraction(1,3), true), &testsPassed);
	printTestResult(test93_94(new NaturalFraction(2,3), new NaturalFraction(2,3), false), &testsPassed);

	printf("\n----comparing two fractions (>=)----\n\n");
	printTestResult(test95_96(new NaturalFraction(2,3), new NaturalFraction(1,3), true), &testsPassed);
	printTestResult(test95_96(new NaturalFraction(2,3), new NaturalFraction(2,3), true), &testsPassed);

	printf("\n----comparing two fractions (<)----\n\n");
	printTestResult(test97_98(new NaturalFraction(5,8), new NaturalFraction(11,8), true), &testsPassed);
	printTestResult(test97_98(new NaturalFraction(5,8), new NaturalFraction(3,8), false), &testsPassed);

	printf("\n----comparing two fractions (<=)----\n\n");
	printTestResult(test99_100(new NaturalFraction(5,8), new NaturalFraction(5,8), true), &testsPassed);
	printTestResult(test99_100(new NaturalFraction(5,8), new NaturalFraction(3,8), false), &testsPassed);

	printf("\n----comparing a fraction with a number (>)----\n\n");
	printTestResult(test101_102(new NaturalFraction(2,3), 0, true), &testsPassed);
	printTestResult(test101_102(new NaturalFraction(2,3), 1, false), &testsPassed);

	printf("\n----comparing a fraction with a number (>=)----\n\n");
	printTestResult(test103_104(new NaturalFraction(6,3), 1, true), &testsPassed);
	printTestResult(test103_104(new NaturalFraction(6,3), 2, true), &testsPassed);

	printf("\n----comparing a fraction with a number (<)----\n\n");
	printTestResult(test105_106(new NaturalFraction(5,8), 1, true), &testsPassed);
	printTestResult(test105_106(new NaturalFraction(5,8), 2, true), &testsPassed);

	printf("\n----comparing a fraction with a number (<=)----\n\n");
	printTestResult(test107_108(new NaturalFraction(21,7), 2, false), &testsPassed);
	printTestResult(test107_108(new NaturalFraction(21,7), 3, true), &testsPassed);

	printf("\nTests passed: %d/108\n\n", testsPassed);
}

void printTestResult(bool result, int* counter)
{
	if (result)
	{
		printf("test passed\n");
		(*counter)++;
	}
	else printf("TEST FAILED\n");
}

bool test1()
{
	NaturalFraction fr(3, 5);
	printf("Expected: 3, Got: %d; ", fr.getNumerator());
	if (fr.getNumerator() == 3) return true;
	else return false;
}
bool test2()
{
	NaturalFraction fr(5, 8);
	printf("Expected: 8, Got: %d; ", fr.getDenominator());
	if (fr.getDenominator() == 8) return true;
	else return false;
}
bool test3_5(NaturalFraction* fr, int expected)
{
	printf("Expected: %d, Got: %d; ", expected, fr->getIntegerPart());
	if (fr->getIntegerPart() == expected) return true;
	else return false;
}
bool test6_10(NaturalFraction* fr, int expectedNum, int expectedDen)
{
	printf("Expected: %d/%d, Got: %d/%d; ", expectedNum, expectedDen, fr->getNumerator(), fr->getDenominator());
	if (fr->getNumerator() == expectedNum && fr->getDenominator() == expectedDen) return true;
	else return false;
}
bool test11_15(NaturalFraction* fr, double expected)
{
	printf("Expected: %lf, Got: %lf; ", expected, fr->toDouble());
	if (expected == fr->toDouble()) return true;
	else return false;
}
bool test16_20(NaturalFraction* fr, int expectedNum, int expectedDen)
{
	NaturalFraction result = *fr;
	printf("Expected: %d/%d, Got: %d/%d; ", fr->getNumerator(), fr->getDenominator(), result.getNumerator(), result.getDenominator());
	if (result.getNumerator() == expectedNum && result.getDenominator() == expectedDen) return true;
	else return false;
}
bool test21_24(NaturalFraction* fr1, NaturalFraction* fr2, bool expected)
{
	char* expect, * got;
	if (expected)
	{
		expect = new char[5];
		strcpy(expect, "true");
	}
	else
	{
		expect = new char[6];
		strcpy(expect, "false");
	}
	if (*fr1 == *fr2)
	{
		got = new char[5];
		strcpy(got, "true");
	}
	else
	{
		got = new char[6];
		strcpy(got, "false");
	}
	printf("Expected: %s, Got: %s; ", expect, got);
	if ((*fr1 == *fr2) == expected) return true;
	else return false;
}
bool test25_28(NaturalFraction* fr1, NaturalFraction* fr2, bool expected)
{
	char* expect, * got;
	if (expected)
	{
		expect = new char[5];
		strcpy(expect, "true");
	}
	else
	{
		expect = new char[6];
		strcpy(expect, "false");
	}
	if (*fr1 != *fr2)
	{
		got = new char[5];
		strcpy(got, "true");
	}
	else
	{
		got = new char[6];
		strcpy(got, "false");
	}
	printf("Expected: %s, Got: %s; ", expect, got);
	if ((*fr1 != *fr2) == expected) return true;
	else return false;
}
bool test29_33(NaturalFraction* fr1, NaturalFraction* fr2, NaturalFraction* expected)
{
	NaturalFraction result = *fr1 + *fr2;
	printf("Expected: %d/%d, Got: %d/%d; ", expected->getNumerator(), expected->getDenominator(), result.getNumerator(), result.getDenominator());
	if (result == *expected) return true;
	else return false;
}
bool test34_38(NaturalFraction* fr1, NaturalFraction* fr2, NaturalFraction* expected)
{
	*fr1 += *fr2;
	printf("Expected: %d/%d, Got: %d/%d; ", expected->getNumerator(), expected->getDenominator(), fr1->getNumerator(), fr1->getDenominator());
	if (*fr1 == *expected) return true;
	else return false;
}
bool test39_41(NaturalFraction* fr, int term, NaturalFraction* expected)
{
	NaturalFraction result = *fr + term;
	printf("Expected: %d/%d, Got: %d/%d; ", expected->getNumerator(), expected->getDenominator(), result.getNumerator(), result.getDenominator());
	if (result == *expected) return true;
	else return false;
}
bool test42_44(NaturalFraction* fr, int term, NaturalFraction* expected)
{
	*fr += term;
	printf("Expected: %d/%d, Got: %d/%d; ", expected->getNumerator(), expected->getDenominator(), fr->getNumerator(), fr->getDenominator());
	if (*fr == *expected) return true;
	else return false;
}
bool test45_49(NaturalFraction* fr1, NaturalFraction* fr2, NaturalFraction* expected)
{
	NaturalFraction result = *fr1 - *fr2;
	printf("Expected: %d/%d, Got: %d/%d; ", expected->getNumerator(), expected->getDenominator(), result.getNumerator(), result.getDenominator());
	if (result == *expected) return true;
	else return false;
}
bool test50_54(NaturalFraction* fr1, NaturalFraction* fr2, NaturalFraction* expected)
{
	*fr1 -= *fr2;
	printf("Expected: %d/%d, Got: %d/%d; ", expected->getNumerator(), expected->getDenominator(), fr1->getNumerator(), fr1->getDenominator());
	if (*fr1 == *expected) return true;
	else return false;
}
bool test55_57(NaturalFraction* fr, int term, NaturalFraction* expected)
{
	NaturalFraction result = *fr - term;
	printf("Expected: %d/%d, Got: %d/%d; ", expected->getNumerator(), expected->getDenominator(), result.getNumerator(), result.getDenominator());
	if (result == *expected) return true;
	else return false;
}
bool test58_60(NaturalFraction* fr, int term, NaturalFraction* expected)
{
	*fr -= term;
	printf("Expected: %d/%d, Got: %d/%d; ", expected->getNumerator(), expected->getDenominator(), fr->getNumerator(), fr->getDenominator());
	if (*fr == *expected) return true;
	else return false;
}
bool test61_63(NaturalFraction* fr1, NaturalFraction* fr2, NaturalFraction* expected)
{
	NaturalFraction result = *fr1 * *fr2;
	printf("Expected: %d/%d, Got: %d/%d; ", expected->getNumerator(), expected->getDenominator(), result.getNumerator(), result.getDenominator());
	if (result == *expected) return true;
	else return false;
}
bool test64_66(NaturalFraction* fr1, NaturalFraction* fr2, NaturalFraction* expected)
{
	*fr1 *= *fr2;
	printf("Expected: %d/%d, Got: %d/%d; ", expected->getNumerator(), expected->getDenominator(), fr1->getNumerator(), fr1->getDenominator());
	if (*fr1 == *expected) return true;
	else return false;
}
bool test67_69(NaturalFraction* fr1, int term, NaturalFraction* expected)
{
	NaturalFraction result = *fr1 * term;
	printf("Expected: %d/%d, Got: %d/%d; ", expected->getNumerator(), expected->getDenominator(), result.getNumerator(), result.getDenominator());
	if (result == *expected) return true;
	else return false;
}
bool test70_72(NaturalFraction* fr1, int term, NaturalFraction* expected)
{
	*fr1 *= term;
	printf("Expected: %d/%d, Got: %d/%d; ", expected->getNumerator(), expected->getDenominator(), fr1->getNumerator(), fr1->getDenominator());
	if (*fr1 == *expected) return true;
	else return false;
}
bool test73_75(NaturalFraction* fr1, NaturalFraction* fr2, NaturalFraction* expected)
{
	NaturalFraction result = *fr1 / *fr2;
	printf("Expected: %d/%d, Got: %d/%d; ", expected->getNumerator(), expected->getDenominator(), result.getNumerator(), result.getDenominator());
	if (result == *expected) return true;
	else return false;
}
bool test76_78(NaturalFraction* fr1, NaturalFraction* fr2, NaturalFraction* expected)
{
	*fr1 /= *fr2;
	printf("Expected: %d/%d, Got: %d/%d; ", expected->getNumerator(), expected->getDenominator(), fr1->getNumerator(), fr1->getDenominator());
	if (*fr1 == *expected) return true;
	else return false;
}
bool test79_81(NaturalFraction* fr1, int term, NaturalFraction* expected)
{
	NaturalFraction result = *fr1 / term;
	printf("Expected: %d/%d, Got: %d/%d; ", expected->getNumerator(), expected->getDenominator(), result.getNumerator(), result.getDenominator());
	if (result == *expected) return true;
	else return false;
}
bool test82_84(NaturalFraction* fr1, int term, NaturalFraction* expected)
{
	*fr1 /= term;
	printf("Expected: %d/%d, Got: %d/%d; ", expected->getNumerator(), expected->getDenominator(), fr1->getNumerator(), fr1->getDenominator());
	if (*fr1 == *expected) return true;
	else return false;
}
bool test85_86(NaturalFraction* fr, NaturalFraction* expected)
{
	++(*fr);
	if (*fr == *expected) return true;
	else return false;
}
bool test87_88(NaturalFraction* fr, NaturalFraction* expected)
{
	(*fr)++;
	if (*fr == *expected) return true;
	else return false;
}
bool test89_90(NaturalFraction* fr, NaturalFraction* expected)
{
	--(*fr);
	if (*fr == *expected) return true;
	else return false;
}
bool test91_92(NaturalFraction* fr, NaturalFraction* expected)
{
	(*fr)--;
	if (*fr == *expected) return true;
	else return false;
}
bool test93_94(NaturalFraction* fr1, NaturalFraction* fr2, bool expected)
{
	char* expect, * got;
	if (expected)
	{
		expect = new char[5];
		strcpy(expect, "true");
	}
	else
	{
		expect = new char[6];
		strcpy(expect, "false");
	}
	if (*fr1 > *fr2)
	{
		got = new char[5];
		strcpy(got, "true");
	}
	else
	{
		got = new char[6];
		strcpy(got, "false");
	}
	printf("Expected: %s, Got: %s; ", expect, got);
	if ((*fr1 > *fr2) == expected) return true;
	else return false;
}
bool test95_96(NaturalFraction* fr1, NaturalFraction* fr2, bool expected)
{
	char* expect, * got;
	if (expected)
	{
		expect = new char[5];
		strcpy(expect, "true");
	}
	else
	{
		expect = new char[6];
		strcpy(expect, "false");
	}
	if (*fr1 >= *fr2)
	{
		got = new char[5];
		strcpy(got, "true");
	}
	else
	{
		got = new char[6];
		strcpy(got, "false");
	}
	printf("Expected: %s, Got: %s; ", expect, got);
	if ((*fr1 >= *fr2) == expected) return true;
	else return false;
}
bool test97_98(NaturalFraction* fr1, NaturalFraction* fr2, bool expected)
{
	char* expect, * got;
	if (expected)
	{
		expect = new char[5];
		strcpy(expect, "true");
	}
	else
	{
		expect = new char[6];
		strcpy(expect, "false");
	}
	if (*fr1 < *fr2)
	{
		got = new char[5];
		strcpy(got, "true");
	}
	else
	{
		got = new char[6];
		strcpy(got, "false");
	}
	printf("Expected: %s, Got: %s; ", expect, got);
	if ((*fr1 < *fr2) == expected) return true;
	else return false;
}
bool test99_100(NaturalFraction* fr1, NaturalFraction* fr2, bool expected)
{
	char* expect, * got;
	if (expected)
	{
		expect = new char[5];
		strcpy(expect, "true");
	}
	else
	{
		expect = new char[6];
		strcpy(expect, "false");
	}
	if (*fr1 <= *fr2)
	{
		got = new char[5];
		strcpy(got, "true");
	}
	else
	{
		got = new char[6];
		strcpy(got, "false");
	}
	printf("Expected: %s, Got: %s; ", expect, got);
	if ((*fr1 <= *fr2) == expected) return true;
	else return false;
}
bool test101_102(NaturalFraction* fr, int number, bool expected)
{
	char* expect, * got;
	if (expected)
	{
		expect = new char[5];
		strcpy(expect, "true");
	}
	else
	{
		expect = new char[6];
		strcpy(expect, "false");
	}
	if (*fr > number)
	{
		got = new char[5];
		strcpy(got, "true");
	}
	else
	{
		got = new char[6];
		strcpy(got, "false");
	}
	printf("Expected: %s, Got: %s; ", expect, got);
	if ((*fr > number) == expected) return true;
	else return false;
}
bool test103_104(NaturalFraction* fr, int number, bool expected)
{
	char* expect, * got;
	if (expected)
	{
		expect = new char[5];
		strcpy(expect, "true");
	}
	else
	{
		expect = new char[6];
		strcpy(expect, "false");
	}
	if (*fr >= number)
	{
		got = new char[5];
		strcpy(got, "true");
	}
	else
	{
		got = new char[6];
		strcpy(got, "false");
	}
	printf("Expected: %s, Got: %s; ", expect, got);
	if ((*fr >= number) == expected) return true;
	else return false;
}
bool test105_106(NaturalFraction* fr, int number, bool expected)
{
	char* expect, * got;
	if (expected)
	{
		expect = new char[5];
		strcpy(expect, "true");
	}
	else
	{
		expect = new char[6];
		strcpy(expect, "false");
	}
	if (*fr < number)
	{
		got = new char[5];
		strcpy(got, "true");
	}
	else
	{
		got = new char[6];
		strcpy(got, "false");
	}
	printf("Expected: %s, Got: %s; ", expect, got);
	if ((*fr < number) == expected) return true;
	else return false;
}
bool test107_108(NaturalFraction* fr, int number, bool expected)
{
	char* expect, * got;
	if (expected)
	{
		expect = new char[5];
		strcpy(expect, "true");
	}
	else
	{
		expect = new char[6];
		strcpy(expect, "false");
	}
	if (*fr <= number)
	{
		got = new char[5];
		strcpy(got, "true");
	}
	else
	{
		got = new char[6];
		strcpy(got, "false");
	}
	printf("Expected: %s, Got: %s; ", expect, got);
	if ((*fr <= number) == expected) return true;
	else return false;
}
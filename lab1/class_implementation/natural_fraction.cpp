#define _CRT_SECURE_NO_WARNINGS

#include "natural_fraction.h"
#include <iostream>

using namespace std;

NaturalFraction::NaturalFraction()
{
	setNumerator(1);
	setDenominator(1);
}
NaturalFraction::NaturalFraction(int num, int den)
{
	setNumerator(num);
	setDenominator(den);
}
NaturalFraction::NaturalFraction(const NaturalFraction& currFraction)
{
	setNumerator(currFraction.numerator);
	setDenominator(currFraction.denominator);
}

int NaturalFraction::getNumerator() { return numerator; }
int NaturalFraction::getDenominator() { return denominator; }
void NaturalFraction::setNumerator(int newNum) 
{ 
	numerator = newNum; 
	numeratorSet = true;
	reduce();
}
void NaturalFraction::setDenominator(int newDen) 
{ 
	denominator = newDen; 
	denominatorSet = true;
	reduce();
}
int NaturalFraction::getIntegerPart() { return numerator / denominator; }
void NaturalFraction::reduce() 
{ 
	if (!numeratorSet || !denominatorSet) return;
	int less = (numerator < denominator) ? numerator : denominator;
	for (int currdivisor = 2; currdivisor <= less; currdivisor++)
	{
		if (numerator % currdivisor == 0 && denominator % currdivisor == 0)
		{
			numerator /= currdivisor;
			denominator /= currdivisor;
			currdivisor--;
		}
	}
}
double NaturalFraction::toDouble()
{
	double numeratorDouble = numerator * 1.0;
	return numeratorDouble / denominator;
}

NaturalFraction NaturalFraction::operator+(const NaturalFraction& term)
{
	NaturalFraction result;
	result.setDenominator(term.denominator * denominator);
	result.setNumerator(numerator * term.denominator + term.numerator * denominator);
	return result;
}
NaturalFraction NaturalFraction::operator+(int term)
{
	NaturalFraction result;
	result.setDenominator(denominator);
	result.setNumerator(numerator + term * denominator);
	return result;
}
NaturalFraction NaturalFraction::operator-(int term)
{
	NaturalFraction result;
	result.setDenominator(denominator);
	result.setNumerator(numerator - term * denominator);
	return result;
}
NaturalFraction NaturalFraction::operator/(int term)
{
	NaturalFraction result;
	result.setNumerator(numerator);
	result.setDenominator(denominator * term);
	return result;
}

void NaturalFraction::operator+=(const NaturalFraction& term)
{
	int tempdenominator = denominator;
	denominator = term.denominator * denominator;
	numerator = numerator * term.denominator + term.numerator * tempdenominator;
	reduce();
}
void NaturalFraction::operator+=(int term)
{
	setNumerator(numerator + term * denominator);
}
void NaturalFraction::operator-=(int term)
{
	setNumerator(numerator - term * denominator);
}
void NaturalFraction::operator/=(int term)
{
	setDenominator(denominator * term);
}

void NaturalFraction::operator=(const NaturalFraction& term)
{
	numerator = term.numerator;
	denominator = term.denominator;
}

bool NaturalFraction::operator==(const NaturalFraction& term)
{
	if (numerator == term.numerator && denominator == term.denominator) return true;
	else return false;
}
bool NaturalFraction::operator!=(const NaturalFraction& term)
{
	if (numerator != term.numerator || denominator != term.denominator) return true;
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

	/*printf("\n----adding two fractions (+=)----\n\n");
	printTestResult(test34_38(new NaturalFraction(1, 3), new NaturalFraction(1, 3), new NaturalFraction(2, 3)), &testsPassed);
	printTestResult(test34_38(new NaturalFraction(5, 8), new NaturalFraction(4, 2), new NaturalFraction(21, 8)), &testsPassed);
	printTestResult(test34_38(new NaturalFraction(12, 11), new NaturalFraction(8, 31), new NaturalFraction(460, 341)), &testsPassed);
	printTestResult(test34_38(new NaturalFraction(29, 100), new NaturalFraction(90, 17), new NaturalFraction(9493, 1700)), &testsPassed);
	printTestResult(test34_38(new NaturalFraction(37821, 1274), new NaturalFraction(6437, 5178), new NaturalFraction(7287067, 235599)), &testsPassed);*/

	printf("\n----adding a number to a fraction (+)----\n\n");
	printTestResult(test39_41(new NaturalFraction(1,3), 2, new NaturalFraction(7,3)), &testsPassed);
	printTestResult(test39_41(new NaturalFraction(29,11), 19, new NaturalFraction(238,11)), &testsPassed);
	printTestResult(test39_41(new NaturalFraction(139,23), 123, new NaturalFraction(2968,23)), &testsPassed);

	printf("\n----adding a number to a fraction (+=)----\n\n");
	printTestResult(test42_44(new NaturalFraction(1, 3), 2, new NaturalFraction(7, 3)), &testsPassed);
	printTestResult(test42_44(new NaturalFraction(29, 11), 19, new NaturalFraction(238, 11)), &testsPassed);
	printTestResult(test42_44(new NaturalFraction(139, 23), 123, new NaturalFraction(2968, 23)), &testsPassed);

	/*printf("\n----subtracting a fraction from a fraction (-)----\n\n");
	printTestResult(test45_49(new NaturalFraction(4,7), new NaturalFraction(1,7), new NaturalFraction(3,7)), &testsPassed);
	printTestResult(test45_49(new NaturalFraction(11,13), new NaturalFraction(2,13), new NaturalFraction(9,13)), &testsPassed);
	printTestResult(test45_49(new NaturalFraction(16,7), new NaturalFraction(2,9), new NaturalFraction(130,63)), &testsPassed);
	printTestResult(test45_49(new NaturalFraction(78,17), new NaturalFraction(13,9), new NaturalFraction(481,153)), &testsPassed);
	printTestResult(test45_49(new NaturalFraction(139235,19), new NaturalFraction(89,1294), new NaturalFraction(180168399,24586)), &testsPassed);*/

	/*printf("\n----subtracting a fraction from a fraction (-=)----\n\n");
	printTestResult(test50_54(new NaturalFraction(4,7), new NaturalFraction(1,7), new NaturalFraction(3,7)), &testsPassed);
	printTestResult(test50_54(new NaturalFraction(11,13), new NaturalFraction(2,13), new NaturalFraction(9,13)), &testsPassed);
	printTestResult(test50_54(new NaturalFraction(16,7), new NaturalFraction(2,9), new NaturalFraction(130,63)), &testsPassed);
	printTestResult(test50_54(new NaturalFraction(78,17), new NaturalFraction(13,9), new NaturalFraction(481,153)), &testsPassed);
	printTestResult(test50_54(new NaturalFraction(139235,19), new NaturalFraction(89,1294), new NaturalFraction(180168399,24586)), &testsPassed);*/

	printf("\n----subtracting a number from a fraction (-)----\n\n");
	printTestResult(test55_57(new NaturalFraction(14,9), 1, new NaturalFraction(5,9)), &testsPassed);
	printTestResult(test55_57(new NaturalFraction(78,15), 3, new NaturalFraction(33,15)), &testsPassed);
	printTestResult(test55_57(new NaturalFraction(1259,7), 42, new NaturalFraction(965,7)), &testsPassed);

	printf("\n----subtracting a number from a fraction (-=)----\n\n");
	printTestResult(test58_60(new NaturalFraction(14, 9), 1, new NaturalFraction(5, 9)), &testsPassed);
	printTestResult(test58_60(new NaturalFraction(78, 15), 3, new NaturalFraction(33, 15)), &testsPassed);
	printTestResult(test58_60(new NaturalFraction(1259, 7), 42, new NaturalFraction(965, 7)), &testsPassed);

	/*printf("\n----multiplying a fraction by a fraction (*)----\n\n");
	printTestResult(test61_63(new NaturalFraction(2,5), new NaturalFraction(14,3), new NaturalFraction(28,15)), &testsPassed);
	printTestResult(test61_63(new NaturalFraction(29,5), new NaturalFraction(12,11), new NaturalFraction(348,55)), &testsPassed);
	printTestResult(test61_63(new NaturalFraction(1298,413), new NaturalFraction(234,2358), new NaturalFraction(303732,973854)), &testsPassed);*/

	/*printf("\n----multiplying a fraction by a fraction (*=)----\n\n");
	printTestResult(test64_66(new NaturalFraction(2,5), new NaturalFraction(14,3), new NaturalFraction(28,15)), &testsPassed);
	printTestResult(test64_66(new NaturalFraction(29,5), new NaturalFraction(12,11), new NaturalFraction(348,55)), &testsPassed);
	printTestResult(test64_66(new NaturalFraction(1298,413), new NaturalFraction(234,2358), new NaturalFraction(303732,973854)), &testsPassed);*/

	/*printf("\n----multiplying a fraction by a number (*)----\n\n");
	printTestResult(test67_69(new NaturalFraction(2,3), 4, new NaturalFraction(8,3)), &testsPassed);
	printTestResult(test67_69(new NaturalFraction(10,7), 7, new NaturalFraction(10,1)), &testsPassed);
	printTestResult(test67_69(new NaturalFraction(265,11), 22, new NaturalFraction(530,1)), &testsPassed);*/

	/*printf("\n----multiplying a fraction by a number (*=)----\n\n");
	printTestResult(test70_72(new NaturalFraction(2,3), 4, new NaturalFraction(8,3)), &testsPassed);
	printTestResult(test70_72(new NaturalFraction(10,7), 7, new NaturalFraction(10,1)), &testsPassed);
	printTestResult(test70_72(new NaturalFraction(265,11), 22, new NaturalFraction(530,1)), &testsPassed);*/

	/*printf("\n----dividing a fraction by a fraction (/)----\n\n");
	printTestResult(test73_75(new NaturalFraction(16,7), new NaturalFraction(7,2), new NaturalFraction(32,49)), &testsPassed);
	printTestResult(test73_75(new NaturalFraction(29,5), new NaturalFraction(1,25), new NaturalFraction(145,1)), &testsPassed);
	printTestResult(test73_75(new NaturalFraction(1298,413), new NaturalFraction(234,2358), new NaturalFraction(3060684,96642)), &testsPassed);*/

	/*printf("\n----dividing a fraction by a fraction (/=)----\n\n");
	printTestResult(test76_78(new NaturalFraction(16,7), new NaturalFraction(7,2), new NaturalFraction(32,49)), &testsPassed);
	printTestResult(test76_78(new NaturalFraction(29,5), new NaturalFraction(1,25), new NaturalFraction(145,1)), &testsPassed);
	printTestResult(test76_78(new NaturalFraction(1298,413), new NaturalFraction(234,2358), new NaturalFraction(3060684,96642)), &testsPassed);*/

	printf("\n----dividing a fraction by a number (/)----\n\n");
	printTestResult(test79_81(new NaturalFraction(8,3), 4, new NaturalFraction(2,3)), &testsPassed);
	printTestResult(test79_81(new NaturalFraction(10,7), 10, new NaturalFraction(1,7)), &testsPassed);
	printTestResult(test79_81(new NaturalFraction(99,11), 9, new NaturalFraction(1,1)), &testsPassed);

	printf("\n----dividing a fraction by a number (/=)----\n\n");
	printTestResult(test82_84(new NaturalFraction(8,3), 4, new NaturalFraction(2,3)), &testsPassed);
	printTestResult(test82_84(new NaturalFraction(10,7), 10, new NaturalFraction(1,7)), &testsPassed);
	printTestResult(test82_84(new NaturalFraction(99,11), 9, new NaturalFraction(1,1)), &testsPassed);

	printf("\nTests passed: %d out of 84\n\n", testsPassed);
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
/*bool test45_49(NaturalFraction* fr1, NaturalFraction* fr2, NaturalFraction* expected)
{
	NaturalFraction result = *fr1 - *fr2;
	printf("Expected: %d/%d, Got: %d/%d; ", expected->getNumerator(), expected->getDenominator(), result.getNumerator(), result.getDenominator());
	if (result == *expected) return true;
	else return false;
}*/
/*bool test50_54(NaturalFraction* fr1, NaturalFraction* fr2, NaturalFraction* expected)
{
	*fr1 -= *fr2;
	printf("Expected: %d/%d, Got: %d/%d; ", expected->getNumerator(), expected->getDenominator(), result.getNumerator(), result.getDenominator());
	if (*fr1 == *expected) return true;
	else return false;
}*/
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
/*bool test61_63(NaturalFraction* fr1, NaturalFraction* fr2, NaturalFraction* expected)
{
	NaturalFraction result = *fr1 * *fr2;
	printf("Expected: %d/%d, Got: %d/%d; ", expected->getNumerator(), expected->getDenominator(), result.getNumerator(), result.getDenominator());
	if (result == *expected) return true;
	else return false;
}*/
/*bool test64_66(NaturalFraction* fr1, NaturalFraction* fr2, NaturalFraction* expected)
{
	*fr1 *= *fr2;
	printf("Expected: %d/%d, Got: %d/%d; ", expected->getNumerator(), expected->getDenominator(), fr1->getNumerator(), fr1->getDenominator());
	if (*fr1 == *expected) return true;
	else return false;
}*/
/*bool test67_69(NaturalFraction* fr1, int term, NaturalFraction* expected)
{
	NaturalFraction result = *fr1 * term;
	printf("Expected: %d/%d, Got: %d/%d; ", expected->getNumerator(), expected->getDenominator(), result.getNumerator(), result.getDenominator());
	if (result == *expected) return true;
	else return false;
}*/
/*bool test70_72(NaturalFraction* fr1, int term, NaturalFraction* expected)
{
	*fr1 *= term;
	printf("Expected: %d/%d, Got: %d/%d; ", expected->getNumerator(), expected->getDenominator(), fr1->getNumerator(), fr1->getDenominator());
	if (*fr1 == *expected) return true;
	else return false;
}*/
/*bool test73_75(NaturalFraction* fr1, NaturalFraction* fr2, NaturalFraction* expected)
{
	NaturalFraction result = *fr1 / *fr2;
	printf("Expected: %d/%d, Got: %d/%d; ", expected->getNumerator(), expected->getDenominator(), result.getNumerator(), result.getDenominator());
	if (result == *expected) return true;
	else return false;
}*/
/*bool test76_78(NaturalFraction* fr1, NaturalFraction* fr2, NaturalFraction* expected)
{
	*fr1 /= *fr2;
	printf("Expected: %d/%d, Got: %d/%d; ", expected->getNumerator(), expected->getDenominator(), fr1->getNumerator(), fr1->getDenominator());
	if (*fr1 == *expected) return true;
	else return false;
}*/
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
#include "lab4header.h"
#include <iostream>

int main()
{
	GeometricVector a(1, 2, 3);
	GeometricVector b(2, 2, 3);
	if (a > b) printf("true");
	else printf("false");
	return 0;
}
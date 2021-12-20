#include "lab4header.h"
#include <iostream>

int main()
{
	GeometricVector e(4, 2, 0);
	GeometricVector b(2, 2, 3);
	GeometricVector c(3, 2, 2);
	GeometricVector f(6, 9, 0);
	GeometricVector d(2, 2, 9);
	GeometricVector a(1, 2, 3);
	std::vector<GeometricVector> input {f, e, a, c, d, b};
	/*std::vector<GeometricVector> result = bucket_sort(input, 3);
	for (int i = 0; i < result.size(); i++) std::cout << result[i];*/
	selection_sort(input);
	for (int i = 0; i < input.size(); i++) std::cout << input[i];
	return 0;
}
#include "lab4header.h"
#include "math.h"

GeometricVector::GeometricVector() {};
GeometricVector::GeometricVector(double x_in, double y_in, double z_in)
{
	x = x_in;
	y = y_in;
	z = z_in;
}

double GeometricVector::get_modulus()
{
	return sqrt(x*x + y*y + z*z);
}

bool GeometricVector::operator>(GeometricVector& comparing)
{
	return this->get_modulus() > comparing.get_modulus();
}
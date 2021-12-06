class GeometricVector
{
private:
	double x = 0, y = 0, z = 0;
public:
	GeometricVector();
	GeometricVector(double x, double y, double z);
	double get_modulus();
	bool operator>(GeometricVector& comparing);
};
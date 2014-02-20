#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#include <cmath>

struct Vector3
{
	Vector3()
	{
		// They are normally set to 500 so they
		// are off-camera as the default ******
		xCoord = yCoord = zCoord = 0;
	}

	Vector3(long double x, long double y, long double z)
	{
		xCoord = x;
		yCoord = y;
		zCoord = z;
	}

public:
	// accessors
	inline long double	x() { return xCoord; }
	inline long double	y() { return yCoord; }
	inline long double	z() { return zCoord; }

	// used for adding
	// *** ALTERS THE VECTOR ***!!!!
	Vector3	add(Vector3 vec)
	{
		x(xCoord + vec.x());
		y(yCoord + vec.y());
		z(zCoord + vec.z());
		return Vector3(x(), y(), z());
	}
	// used for subtracting
	// *** ALTERS THE VECTOR ***!!!!
	Vector3	subtract(Vector3 vec)
	{
		x(xCoord - vec.x());
		y(yCoord - vec.y());
		z(zCoord - vec.z());
		return Vector3(x(), y(), z());
	}
	// used for scalar multiplication
	// *** ALTERS THE VECTOR ***!!!!
	Vector3 scalarMult(double scalar)
	{
		x(xCoord * scalar);
		y(yCoord * scalar);
		z(zCoord * scalar);
		return Vector3(x(), y(), z());
	}
	// used for scalar division
	// *** ALTERS THE VECTOR ***!!!!
	Vector3 scalarDiv(double scalar)
	{
		x(xCoord / scalar);
		y(yCoord / scalar);
		z(zCoord / scalar);
		return Vector3(x(xCoord / scalar), y(yCoord / scalar), z(zCoord / scalar));
	}
	// computes the unit vector
	// (normalized vector)
	// *** ALTERS THE VECTOR ***!!!!
	Vector3 unitVector()
	{
		return scalarDiv(mag());
	}
	// used for finding magnitude of vector
	// *** does NOT alter the vector ***
	double mag()
	{
		return sqrt(pow(x(),2)+pow(y(),2)+pow(z(),2));	
	}

	// overloaded to be mutators
	inline long double	x( long double num ) { return (xCoord = num); }
	inline long double	y( long double num ) { return (yCoord = num); }
	inline long double	z( long double num ) { return (zCoord = num); }


private:
	long double	xCoord;
	long double	yCoord;
	long double	zCoord;
};

#endif	//__VECTOR_3__
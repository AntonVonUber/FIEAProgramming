#ifndef __VECTOR_2D_H__
#define __VECTOR_2D_H__

#include <cmath>
#include <string>
#include <fstream>
#include <iostream>

struct Vector2D
{
	double x;
	double y;
	const double tol;

	Vector2D():tol(0.0001) { x = 0.0f; y = 0.0f; };
	Vector2D(double a, double b):x(a),y(b),tol(0.0001) { };
	// returns a unit vector at the angle entered
	Vector2D(double angle):x(cos(angle)),y(sin(angle)),tol(0.0001) { };

	// copy and assignment constructors
	Vector2D(const Vector2D &rhs):x(rhs.x),y(rhs.y),tol(0.0001) { };
	Vector2D& operator=(const Vector2D &rhs)
		{ x = rhs.x; y = rhs.y; return *this; };

	// sets x and y to zero
	inline void zero()
		{ x=0; y=0; };

	//returns true if both x and y are zero
	inline bool isZero() const
		{ return (x == 0 && y == 0); };

	//returns the length of the vector
	inline double length() const
		{ return (sqrt(x*x + y*y)); };

	//returns the squared length of the vector (thereby avoiding the sqrt)
	inline double lengthSq() const
		{ return (x*x + y*y); };

	inline void normalize()
		{ double l = length();
		if(l <= tol) l = 1; x/=l; y/=l;
		if(fabs(x) < tol) x = 0.0f; if(fabs(y) < tol) y = 0.0f; };
	inline Vector2D returnNormal() const
		{ double l = length();
		if(l <= tol) l = 1; double tempX = x/l; double tempY = y/l;
		if(fabs(tempX) < tol) tempX = 0.0f;
		if(fabs(tempY) < tol) tempY = 0.0f;
		return Vector2D(tempX, tempY); };

	//returns the dot product of this and v2
	inline double dot(const Vector2D& v2) const
		{ return (x*v2.x + y*v2.y); };

	// returns positive if v2 is clockwise of this vector,
	// negative if counterclockwise (assuming the Y axis is pointing down,
	// X axis to right like a Window app)
	inline int sign(const Vector2D& v2) const
		{	double result = x*v2.y - v2.x*y;
			if(result > 0) return -1;
			else if(result < 0) return 1; return 0; };

	//returns the vector that is perpendicular to this one
	inline Vector2D perp()const
		{ return Vector2D(y, -x); };	// not done yet...

	//adjusts x and y so that the length of the vector does not exceed max
	inline void truncate(double max)
		{	double l = length();
			if(l > max) { normalize(); x*=max; y*=max; } };
	inline Vector2D returnTruncated(double max)
		{	double l = length(); if(l > max) { Vector2D temp = this->returnNormal();
			temp.x*=max; temp.y*=max; return temp; } };

	//returns the distance between this vector and the one passed as a parameter
	inline double distance(const Vector2D &v2) const
		{ return (sqrt(((x-v2.x)*(x-v2.x)) + ((y-v2.y)*(y-v2.y)))); };

	//squared version of above
	inline double distanceSq(const Vector2D &v2) const
		{ return (((x-v2.x)*(x-v2.x)) + ((y-v2.y)*(y-v2.y))); };

	//reverses this vector
	inline void reverse() { x=-x; y=-y; }
	//returns the vector that is the reverse of this vector
	inline Vector2D getReverse() const { return Vector2D(-x,-y); };

	//we need some operators
	inline const Vector2D& operator+=(const Vector2D &rhs)
		{ x+=rhs.x; y+=rhs.y; return *this; };
	inline const Vector2D& operator-=(const Vector2D &rhs)
		{ x-=rhs.x; y-=rhs.y; return *this; };
	template <typename t>
	inline const Vector2D& operator*=(const t& rhs)
		{ x*=rhs; y*=rhs; return *this; };
	template <typename t>
	inline const Vector2D& operator/=(const t& rhs)
		{ x/=rhs; y/=rhs; return *this; };
	inline bool operator==(const Vector2D& rhs) const
		{ return (x == rhs.x && y == rhs.y); };
	inline bool operator!=(const Vector2D& rhs) const
		{ return !(x == rhs.x && y == rhs.y); };

	friend std::ostream& operator<<(std::ostream& os, Vector2D& v);
};

inline std::ostream& operator<<(std::ostream& os, Vector2D& v)
	{ os << "Vector2D: (" << v.x << ", " << v.y << ")"; return os; };
inline Vector2D operator+(Vector2D& u, Vector2D& v)
	{ return Vector2D(u.x+v.x, u.y+v.y); };
inline Vector2D operator-(Vector2D& u, Vector2D& v)
	{ return Vector2D(u.x-v.x, u.y-v.y); };
template <typename t>
inline Vector2D operator*(Vector2D& u, t num)
	{ return Vector2D(u.x*num, u.y*num); };
template <typename t>
inline Vector2D operator/(Vector2D& u, t num)
	{ return Vector2D(u.x/num, u.y/num); };

#endif	//	__VECTOR_2D_H__
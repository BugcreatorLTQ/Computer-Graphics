#ifndef POINT_H
#define POINT_H

#include<cmath>

//---------------------------------point----------------------------------
template<typename Type>
struct point {
    Type x, y;
    point() { x = y = (Type)0; };
    point(const Type x, const Type y);
    void set(const Type x, const Type y) { this->x = x; this->y = y; };
    point & operator*=(const Type size);
    point operator*(const Type size) const;
    Type operator*(const point & other) const;
    point & operator+=(const point & other);
    point operator+(const point & other) const;
    point & operator-=(const point & other);
    point operator-(const point & other) const;
    bool operator==(const point & other) const;
    Type abs() const;
};

template<typename Type>
point<Type>::point(const Type x,const Type y)
{
	this->x = x;
	this->y = y;
}

template<typename Type>
point<Type> & point<Type>::operator*=(const Type size) 
{
	x *= size;
	y *= size;
	return *this;
}

template<typename Type>
point<Type> point<Type>::operator*(const Type size) const
{
	point temp = *this;
	temp *= size;
	return temp;
}

template<typename Type>
Type point<Type>::operator*(const point<Type> & other) const
{
	return x * other.x + y * other.y;
}

template<typename Type>
point<Type> & point<Type>::operator+=(const point<Type> & other)
{
	x += other.x;
	y += other.y;
	return *this;
}

template<typename Type>
point<Type> point<Type>::operator+(const point<Type> & other) const
{
	point temp = *this;
	temp += other;
	return temp;
}

template<typename Type>
Type point<Type>::abs() const
{
    return (Type)sqrt(x * x + y * y);
}

template<typename Type>
point<Type> &  point<Type>::operator-=(const point<Type> & other)
{
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}

template<typename Type>
point<Type> point<Type>::operator-(const point<Type> & other) const
{
    point<Type> temp = *this;
    temp -= other;
    return temp;
}

template<typename Type>
bool point<Type>::operator==(const point<Type> & other) const
{
    if (this->x == other.x&&this->y == other.y)
        return true;
    else
        return false;
}

#endif // !POINT_H
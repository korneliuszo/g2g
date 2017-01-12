/*
 * Point.h
 *
 *  Created on: Feb 20, 2016
 *      Author: kosa
 */

#ifndef POINT_H_
#define POINT_H_

#include <math.h>
#include <string>

class Point
{
public:
	double x;
	double y;
	Point() : x(0), y(0){};
	Point(double x_, double y_) : x(x_), y(y_){};
	Point operator+(const Point& a) const
	{
		return Point(x+a.x,y+a.y);
	};
	void operator+=(const Point& a)
	{
		x+=a.x;
		y+=a.y;
	};
	Point operator-(const Point& a) const
	{
		return Point(x-a.x,y-a.y);
	};
	Point operator-() const
	{
		return Point(-x,-y);
	};
    bool operator== (const Point& d)
	{
    	return x == d.x && y == d.y;
	}
    bool operator!= (Point &a)
    {
        return !(*this == a);
    }
    double len()
    {
    	return sqrt(x*x+y*y);
    }
    Point div(double d)
    {
    	return Point(x/d,y/d);
    }
    std::string str()
    {
    	return "X" + std::to_string(x) +"Y " + std::to_string(y);
    }
	double operator*(const Point& a) const
	{
		return (x*a.x+y*a.y);
	};
};


#endif /* POINT_H_ */

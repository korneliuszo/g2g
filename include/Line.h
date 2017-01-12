/*
 * Line.h
 *
 *  Created on: Mar 6, 2016
 *      Author: kosa
 */

#ifndef LINE_H_
#define LINE_H_

#include "Point.h"

class Line
{
	//line a*x+b*y=c
	double a;
	double b;
	double c;
	Line() : a(0), b(0), c(){};
	Line(double a_, double b_, double c_) : a(a_), b(b_), c(c_){};
	Line prependicual()
	{
		return Line(

				);
	}
};


#endif /* LINE_H_ */

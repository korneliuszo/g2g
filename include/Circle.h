/*
 * Circle.h
 *
 *  Created on: Feb 20, 2016
 *      Author: kosa
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "Command.h"

#if 0
class Circle : public PlotCommand
{
public:
	double r;
	Circle(double r_): r(r_){};
	virtual PlotCommand* clone() { return new Circle(r); };
	virtual std::string Plot(GcodePlotter* plotter);
};
#else
#include "Poly.h"

class Circle : public RegPoly
{
public:
	Circle(double r): RegPoly(r,50,0){};
};
#endif

#endif /* CIRCLE_H_ */

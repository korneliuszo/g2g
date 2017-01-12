/*
 * Rect.h
 *
 *  Created on: Feb 20, 2016
 *      Author: kosa
 */

#ifndef RECT_H_
#define RECT_H_

#include "Command.h"
#include "Poly.h"

class Rect : public PlotCommand
{
public:
	double x;
	double y;
	Rect(double x_, double y_): x(x_),y(y_) {};
	virtual PlotCommand* clone() { return new Rect(x,y); };
	void set_exposure(Point start_, Point end_) {start=start_;end=end_;};

	virtual std::string Plot(std::shared_ptr<GcodePlotter> plotter);
};


#endif /* OCTAGON_H_ */

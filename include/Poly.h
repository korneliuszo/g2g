/*
 * Poly.h
 *
 *  Created on: Feb 24, 2016
 *      Author: kosa
 */

#ifndef POLY_H_
#define POLY_H_

#include "Command.h"
#include "Point.h"
#include <vector>

class Poly : public PlotCommand
{
public:
	std::vector<Point> nodes;
	Poly(): nodes() {};
	Poly(std::vector<Point> nodes_): nodes(nodes_) {};
	virtual PlotCommand* clone() { return new Poly(nodes); };

	void set_exposure(Point start_, Point end_) {start=start_;end=end_;};
	std::string Plot(std::shared_ptr<GcodePlotter> plotter);
};

class RegPoly : public Poly
{
public:
	double r;
	RegPoly(double r, int n, double fi=0);
	RegPoly(std::vector<Point> nodes_, double r_): Poly(nodes_), r(r_) {};
	virtual PlotCommand* clone() { return new RegPoly(nodes,r); };
	virtual std::string Plot(std::shared_ptr<GcodePlotter> plotter);
};


#endif /* POLY_H_ */

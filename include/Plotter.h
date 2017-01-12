/*
 * Plotter.h
 *
 *  Created on: May 29, 2016
 *      Author: kosa
 */

#ifndef PLOTTER_H_
#define PLOTTER_H_

#include <yaml-cpp/yaml.h>

class Plotter
{
public:
	virtual ~Plotter() {};
	virtual std::string MoveTo(Point to) = 0;
	virtual std::string MoveToFast(Point to) = 0;
	virtual std::string PenDown() = 0;
	virtual std::string PenUp() = 0;
	virtual std::string FillCircle(Point center, double r) = 0;
	virtual std::string FillPoly(std::vector<Point> nodes) = 0;
};



#endif /* PLOTTER_H_ */

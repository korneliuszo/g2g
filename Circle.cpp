/*
 * Circle.cpp
 *
 *  Created on: Mar 1, 2016
 *      Author: kosa
 */

#include "Circle.h"

#if 0
std::string Circle::Plot(GcodePlotter* plotter)
{
	std::stringstream gcode;
	gcode << ";Circle from: "+start.str()+" to: "+end.str()+ "\n";
	gcode << plotter->MoveToFast(start);
	gcode << plotter->FillCircle(start,r);
	if (start != end)
	{
		gcode << plotter->MoveTo(start);
		gcode << plotter->MoveTo(end);
		gcode << plotter->FillCircle(end,r);
	}
	return gcode.str();
}
#endif

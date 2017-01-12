/*
 * Aperture.h
 *
 *  Created on: Feb 20, 2016
 *      Author: kosa
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include "Point.h"
#include "GcodePlotter.h"
#include <string>

class Command
{
public:
	virtual std::string Plot(std::shared_ptr<GcodePlotter> plotter) {return "";};
	virtual ~Command(){};
};

class StringCommand : public Command
{
public:
	std::string command;
	StringCommand(std::string command_): command(command_) {};
	std::string Plot(std::shared_ptr<GcodePlotter> plotter) {return command;};
};

class PlotCommand : public Command
{
public:
	Point start,end;
	PlotCommand(): start(0,0),end(0,0) {};
	virtual PlotCommand* clone() { return new PlotCommand(); };
	void set_exposure(Point start_, Point end_) {start=start_;end=end_;};
	virtual std::string Plot(std::shared_ptr<GcodePlotter> plotter) {return ";PlotCommand\n";};
};

#endif /* APERTURE_H_ */

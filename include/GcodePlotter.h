/*
 * GcodePloter.h
 *
 *  Created on: Feb 22, 2016
 *      Author: kosa
 */

#ifndef GCODEPLOTTER_H_
#define GCODEPLOTTER_H_

#include "Point.h"
#include <yaml-cpp/yaml.h>
#include <string>
#include <sstream>
#include <vector>
#ifdef WITH_CIMG
#include <CImg.h>
#endif

class GcodePlotter
{
private:
	const double dscale=10;
	std::vector<Point> ShrinkNodes(std::vector<Point> nodes);
#ifdef WITH_CIMG
	cimg_library::CImg<float> image;
	cimg_library::CImgDisplay draw_disp;
#endif
	bool debug;
	Point offset;
	double zdown;
	double zup;
	bool pendown;
	Point lastpos;
public:
	double penwidth;
	GcodePlotter(const YAML::Node config);
	GcodePlotter(double penwidth_, Point offset_, double zdown_, double zup_, bool debug_=false);
	std::string MoveTo(Point to,bool absolute=false);
	std::string MoveToFast(Point to,bool absolute=false);
	std::string PenDown();
	std::string PenUp();
	std::string FillCircle(Point center, double r);
	std::string FillPoly(std::vector<Point> nodes);
};


#endif /* GCODEPLOTER_HPP_ */

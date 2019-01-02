/*
 * GcodePlotter.cpp
 *
 *  Created on: Mar 1, 2016
 *      Author: kosa
 */

#include "GcodePlotter.h"

#include <boost/polygon/polygon.hpp>

typedef boost::polygon::point_data<int> point;
typedef boost::polygon::polygon_set_data<int> polygon_set;
typedef boost::polygon::polygon_data<int> polygon;
typedef std::pair<point, point> edge;
using namespace boost::polygon::operators;


GcodePlotter::GcodePlotter(double penwidth_, Point offset_, double zdown_, double zup_, bool debug_)
: penwidth(penwidth_), offset(offset_), zdown(zdown_), zup(zup_), debug(debug_)
{
	if(debug)
	{
		image=cimg_library::CImg<float>(1000,1000,1,1,0);
		draw_disp=cimg_library::CImgDisplay(image,"Intensity profile");
	}
	//image.fill(0);
};

GcodePlotter::GcodePlotter(const YAML::Node config)
:GcodePlotter(config["penwidth"].as<double>()
		,Point(config["offsetX"].as<double>(),config["offsetY"].as<double>())
		,config["zdown"].as<double>()
		,config["zup"].as<double>()
		,config["debug"].as<bool>(false)
		)
{}

std::string GcodePlotter::MoveTo(Point to,bool absolute)
{
	if (!absolute) to+=offset;
	std::stringstream gcode;
	if (isnan(to.x) || isnan(to.y))
		throw "Wololo";
	gcode << "G1 X" << to.x << " Y" << to.y << "\n";
	if (debug && pendown)
	{
		float colour[]={1};
		image.draw_line((int)(lastpos.x*dscale),(int)(lastpos.y*dscale),
				(int)(to.x*dscale),(int)(to.y*dscale),colour);
		image.draw_circle((int)(to.x*dscale),(int)(to.y*dscale),(int)(penwidth/2*dscale),colour);
		image.display(draw_disp);
	}
	lastpos=to;

	return gcode.str();
}
std::string GcodePlotter::MoveToFast(Point to,bool absolute)
{
	if (!absolute) to+=offset;
	std::stringstream gcode;
	if (lastpos !=to)
		gcode << PenUp();
	gcode << "G0 X" << to.x << " Y" << to.y << "\n";
	if (lastpos !=to)
		gcode << PenDown();

	lastpos=to;

	return gcode.str();
}
std::string GcodePlotter::PenDown()
{
	pendown=true;
	if(debug){
		float colour[]={1};
		image.draw_circle((int)(lastpos.x*dscale),(int)(lastpos.y*dscale),(int)(penwidth/2*dscale),colour);
		image.display(draw_disp);
	}
	std::stringstream gcode;
	gcode << "G1 Z" << zdown << "\n";
	return gcode.str();
}
std::string GcodePlotter::PenUp()
{
	pendown=false;
	std::stringstream gcode;
	gcode << "G1 Z" << zup << "\n";
	return gcode.str();
}
std::string GcodePlotter::FillCircle(Point center, double r)
{
#if 0
	std::stringstream gcode;
	for(double i=r-penwidth/2; i>0;i-=penwidth/2)
	{
		Point startpoint=center+Point(i,0);
		Point startpointoff=startpoint+offset;
		gcode << MoveTo(startpoint);
		gcode << "G02 X" << startpointoff.x << " Y" << startpointoff.y <<
				" I" << -i << " J0.000" << "\n";
	}
	if(debug && pendown)
	{
		center+=offset;
		float colour[]={1};
		image.draw_circle((int)(center.x*dscale),(int)(center.y*dscale),(int)(penwidth/2*dscale),colour);
		image.display(draw_disp);
	}
	return gcode.str();

#else
	std::vector<Point> nodes;
	for (double fi=0;fi<=M_PI*2;fi+=1)
	{
		nodes.push_back(Point(sin(fi)*r+center.x,cos(fi)*r+center.y));
	}
	return FillPoly(nodes);
#endif
}
std::vector<Point> GcodePlotter::ShrinkNodes(std::vector<Point> nodes)
{

}
std::string GcodePlotter::FillPoly(std::vector<Point> nodes)
{
	std::stringstream gcode;
	polygon_set a;
	std::vector<point> pts;
	for (auto i: nodes)
		pts.push_back(point(int(i.x*1000), int(i.y*1000)));
	polygon poly;
	boost::polygon::set_points(poly, pts.begin(), pts.end());
	a+=poly;
	int maxvert=0;
	do
	{
		a.resize(-int(penwidth/2*1000),true,10);
		maxvert=0;
		std::vector<polygon> polys;
		polys.clear();
		a.get(polys);
		for(auto it=polys.begin();it<polys.end();it++)
		{
			auto b=it->begin();
			gcode << MoveToFast(Point(b->x()/1000.0,b->y()/1000.0),false);
			for(auto itb=b;itb<it->end();itb++)
			{
				gcode << MoveTo(Point(itb->x()/1000.0,itb->y()/1000.0),false);
				maxvert++;
			}
			gcode << MoveTo(Point(b->x()/1000.0,b->y()/1000.0),false);
		}
		//a.shrink(int(penwidth/2*1000));
		a.clean();
	}
	while(maxvert>2);
	return gcode.str();
}



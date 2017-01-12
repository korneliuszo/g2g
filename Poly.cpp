/*
 * Poly.cpp
 *
 *  Created on: Mar 1, 2016
 *      Author: kosa
 */

#include "Poly.h"
#include <algorithm>

//const Point& min(const Point& a, const Point& b)
//{
//    return (b < a) ? b : a;
//}

std::string Poly::Plot(std::shared_ptr<GcodePlotter> plotter)
{
	auto addstartfunc = [this](Point &a) {a+=start;};
	auto addendfunc = [this](Point &a) {a+=end;};

	if (start != end)
	{
		Point center=start-end;
		Point divline(center.y,center.x);
		std::vector<double> rate;
		rate.resize(nodes.size());
		std::transform(nodes.begin(), nodes.end(),rate.begin(),
				[divline](const Point& a)-> double{
			return a*divline;
		});
		auto minmax = std::minmax_element(rate.begin(), rate.end());
		int break1=minmax.first - rate.begin();
		int break2=minmax.second - rate.begin();
		auto breaks = std::minmax(break1,break2);

		if(nodes[breaks.first!=nodes.size()-1?(breaks.first+1):0]*center<
		   nodes[breaks.first!=0?breaks.first-1:nodes.size()]*center)
		{
			Point b1p=nodes[breaks.first]+start;
			Point b2p=nodes[breaks.second]+end;
			std::for_each(nodes.begin(),nodes.begin()+breaks.first,addstartfunc);
			std::for_each(nodes.begin()+breaks.first,nodes.begin()+breaks.second,addendfunc);
			std::for_each(nodes.begin()+breaks.second,nodes.end(),addstartfunc);
			nodes.insert(nodes.begin()+breaks.second,b2p);
			nodes.insert(nodes.begin()+breaks.first,b1p);
		}
		else
		{
			Point b1p=nodes[breaks.first]+end;
			Point b2p=nodes[breaks.second]+start;
			std::for_each(nodes.begin(),nodes.begin()+breaks.first,addendfunc);
			std::for_each(nodes.begin()+breaks.first,nodes.begin()+breaks.second,addstartfunc);
			std::for_each(nodes.begin()+breaks.second,nodes.end(),addendfunc);
			nodes.insert(nodes.begin()+breaks.second,b2p);
			nodes.insert(nodes.begin()+breaks.first,b1p);
		}
	}
	else
	{
		std::for_each(nodes.begin(),nodes.end(), addstartfunc);
	}
	std::stringstream gcode;
	gcode << ";Poly\n";
	gcode << plotter->MoveToFast(start);
	gcode << plotter->FillPoly(nodes);
	gcode << plotter->MoveTo(end);
	return gcode.str();
}

RegPoly::RegPoly(double r, int n, double fi): r(r)
{
	for(int i=0;i<n;i++)
	{
		nodes.push_back(Point(r*sin(i*2*M_PI/n+fi),r*cos(i*2*M_PI/n+fi)));
	}
};
std::string RegPoly::Plot(std::shared_ptr<GcodePlotter> plotter)
{
	if (r<plotter->penwidth)
	{
		std::stringstream gcode;
		gcode << ";Small Poly\n";
		gcode << plotter->MoveToFast(start);
		gcode << plotter->MoveTo(end);
		return gcode.str();
	}
	else
		return Poly::Plot(plotter);
}


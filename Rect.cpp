/*
 * Rect.cpp
 *
 *  Created on: Mar 1, 2016
 *      Author: kosa
 */

#include "Rect.h"
#include <algorithm>

std::string Rect::Plot(std::shared_ptr<GcodePlotter> plotter)
{
	Point x2(x/2,0);
	Point y2(0,y/2);
	std::vector<Point> nodes=
	{start+x2,start-x2,start+y2,start-y2,
			end  +x2,end  -x2,  end+y2,end  -y2};
	Point move=end-start;
	if (move==Point(0,0))
	{
		nodes=
		{start+x2-y2,start-x2-y2,start-x2+y2,start+x2+y2};
	}
	else if(move.x==0)
	{
		if (move.y>0)
			nodes=
			{start+x2-y2,start-x2-y2,end-x2+y2,end+x2+y2};
		else
			nodes=
			{end+x2-y2,end-x2-y2,start-x2+y2,start+x2+y2};

	}
	else if(move.y==0)
	{
		if (move.x>0)
			nodes=
			{end+x2-y2,start-x2-y2,start-x2+y2,end+x2+y2};
		else
			nodes=
			{start+x2-y2,end-x2+y2,end-x2+y2,start+x2+y2};
	}
	/*
		else if(move.y>0)
		{
			if (move.x>0)
				nodes=
					{end+x2-y2,start+x2-y2,start-x2-y2,start-x2+y2,end-x2+y2,end+x2+y2};
			else
				nodes=
					{end+x2-y2,start+x2-y2,start-x2-y2,start-x2+y2,end-x2+y2,end+x2+y2};
		}
		else if(move.y<0)
		{
			nodes=
				{start+x2,start-x2,start+y2,start-y2,
				end  +x2,end  -x2,  end+y2,end  -y2};
		}*/
	else
	{
		throw "Not supported";
	}
	std::stringstream gcode;
	gcode << ";Rect\n";
	gcode << plotter->MoveToFast(start);
	gcode << plotter->FillPoly(nodes);

	return gcode.str();
}

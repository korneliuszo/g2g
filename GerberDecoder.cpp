/*
 * GerberDecoder.cpp
 *
 *  Created on: Feb 20, 2016
 *      Author: kosa
 */



#include "GerberDecoder.h"
#include "Octagon.h"
#include "Circle.h"
#include "Rect.h"

#include <math.h>

std::shared_ptr<Command> GerberDecoder::processline(std::string line)
{
	if (amoc8)
	{
		// octagon parameters
		if (line.find("%") != std::string::npos)
			amoc8=false;
		return std::make_shared<Command>();
	}
	if (line.find("G75") == 0)
	{
		//quadrant mode
	}
	else if (line.find("%MOIN*%") == 0)
	{
		//inches so enable conversion
		scale=25.4;
		return std::make_shared<StringCommand>("G21\n"); // metric
	}
	else if (line.find("%MOMM*%") == 0)
	{
		//metric so enable conversion
		scale=1;
		return std::make_shared<StringCommand>("G21\n"); // metric
	}	
	else if (line.find("%LPD*%") == 0)
	{
		//we support only dark
	}
	else if (line.find("G01*") == 0)
	{
		//we support only linear mode
	}
	else if (line.find("%OF") == 0)
	{
		//ignore offset
	}
	else if (line.find("%FSLAX") == 0)
	{
		//xy dot point
		int x,y;
		if(sscanf(line.c_str(),"%%FSLAX%dY%d*%%",&x,&y) !=2)
			throw std::string("Not decipherable: "+line);
		dotpointx=x%10;
		dotpointy=y%10;
	}
	else if (line.find("%IPPOS*%") == 0)
	{
		//positive lighting - can do only this
	}
	else if (line.find("%LPD*%") == 0)
	{
		//dark polarity - can do only this
	}
	else if (line.find("%AMOC8*") == 0)
	{
		amoc8=true;
		//octagon shape? - next line has parameters
	}
	else if (line.find("%ADD") == 0)
	{
		//apearture %ADD10C,0.00000*%
		int number=std::stoi(line.substr(4,line.find(",")-4));
		std::string type=line.substr(6,line.find(",")-6);
		if(type == "C")
		{
			double r=std::stod(line.substr(line.find(",")+1))/2;
			apertures[number] = std::make_shared<Circle>(r*scale);
		}
		else if(type == "OC8")
		{
			//hacky
			double factor=1.08239/2;
			double size=std::stod(line.substr(line.find(",")+1));
			apertures[number]=std::make_shared<Octagon>(size*scale*factor);
		}
		else if(type == "R")
		{
			//hacky
			double x=std::stod(line.substr(line.find(",")+1));
			double y=std::stod(line.substr(line.find("X")+1));
			apertures[number]=std::make_shared<Rect>(x*scale,y*scale);
		}
		else
		{
			throw std::string("Not known aperture type: "+line);
		}
		//octagon shape? - next line has parameters
	}
	else if (line.find("D") == 0)
	{
		//select aperture
		int number=std::stoi(line.substr(1));
		current_aperture = apertures[number];
	}
	else if (line.find("G36") == 0)
	{
		g36=true;
	}
	else if (line.find("G37") == 0)
	{
		g36=false;
		Point center;
		for(auto it=g36_poly.begin();it<g36_poly.end();it++)
			center+=*it;
		center.x = center.x / g36_poly.size();
		center.y = center.y / g36_poly.size();
		for(auto it=g36_poly.begin();it<g36_poly.end();it++)
			*it-=center;
		std::shared_ptr<Poly> cmd = std::make_shared<Poly>(g36_poly);
		g36_poly.resize(0);
		cmd->set_exposure(center,center);
		return cmd;
	}
	else if (line.find("X") == 0)
	{
		// lineing!
		//X0001000Y0001000D02*

		double x = scale*std::stoi(line.substr(1,line.find("Y")))/pow(10,dotpointx);
		double y = scale*std::stoi(line.substr(line.find("Y")+1,line.find("D")))/pow(10,dotpointy);
		int d = std::stoi(line.substr(line.find("D")+1));
		if(g36)
		{
			g36_poly.push_back(Point(x,y));
		}
		else
		{
			if (d == 2)
			{
				last_point=Point(x,y);
			}
			else if (d == 1)
			{
				std::shared_ptr<PlotCommand> cmd = std::shared_ptr<PlotCommand>(current_aperture->clone());
				cmd->set_exposure(last_point,Point(x,y));
				last_point=Point(x,y);
				return cmd;
			}
			else if (d == 3)
			{
				std::shared_ptr<PlotCommand> cmd = std::shared_ptr<PlotCommand>(current_aperture->clone());
				cmd->set_exposure(Point(x,y),Point(x,y));
				last_point=Point(x,y);
				return cmd;
			}
		}
	}

	else if (line.find("M02*") == 0)
	{
		//close block
	}
	else if (line.find("G04") == 0)
	{
		//comment
		return std::make_shared<StringCommand>("; "+line+"\n"); // metric
	}	
	else
	{
		throw std::string("Not decipherable: "+line);
	}
	return std::make_shared<Command>();
}

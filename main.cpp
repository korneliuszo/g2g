/*
 * main.cpp
 *
 *  Created on: Feb 20, 2016
 *      Author: kosa
 */

#include <fstream>
#include <iostream>
#include <yaml-cpp/yaml.h>
#include "GerberDecoder.h"
#include "GcodePlotter.h"
#include "Circle.h"

int main(int argv, char ** argc)
{
	if (argv<3)
	{
		std::cout << argc[0] <<" <config> <inprefix> <outprefix>\n";
		return 1;
	}
	const YAML::Node config = YAML::LoadFile(argc[1]);
	const YAML::Node process = config["process"];
	for (YAML::const_iterator it=process.begin();it!=process.end();++it) {
		const YAML::Node process=*it;
		std::ifstream infile(argc[2]+process["in"].as<std::string>());
		std::ofstream outfile(argc[3]+process["out"].as<std::string>());

		std::shared_ptr<GcodePlotter> plotter;
		plotter.reset(new GcodePlotter(process["plotterconfig"]));
		std::shared_ptr<Decoder> decoder;

		std::string decodertype=process["decoder"].as<std::string>();

		if(decodertype == "gerber")
			decoder.reset(new GerberDecoder(process["decoderconfig"]));


		outfile << process["initlines"].as<std::string>();
		outfile << plotter->PenUp();

		std::string line;
		try{
			while (std::getline(infile, line))
			{
				std::string outline = decoder->processline(line)->Plot(plotter);
				outfile << outline;
			}
		}
		catch(std::string obj)
		{
			std::cout << "Error: " << obj << std::endl;
			return 1;
		}
		outfile << plotter->PenUp();
		outfile << plotter->MoveToFast(Point(0,0),true);
		outfile.close();

	}
	return 0;
}

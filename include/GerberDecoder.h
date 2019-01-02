/*
 * GerberDecoder.h
 *
 *  Created on: Feb 20, 2016
 *      Author: kosa
 */

#ifndef GERBERDECODER_H_
#define GERBERDECODER_H_


#include "Decoder.h"
#include <map>
#include <memory>

class GerberDecoder : public Decoder
{
public:
	virtual ~GerberDecoder(){};
	double scale;
	int dotpointx;
	int dotpointy;
	bool amoc8;
	bool g36;
	double flipx;
	double flipy;
	std::vector<Point> g36_poly;
	std::map<int,std::shared_ptr<PlotCommand>> apertures;
	Point last_point;
	std::shared_ptr<PlotCommand> current_aperture;
	GerberDecoder() :dotpointx(0), dotpointy(0), scale(1), amoc8(false), g36(false),
			flipx(1), flipy(1) {};
	GerberDecoder(const YAML::Node config) :
		dotpointx(0), dotpointy(0), scale(1), amoc8(false), g36(false)
	{
		flipx=(config["flipx"].as<bool>(false))?-1:1;
		flipy=(config["flipy"].as<bool>(false))?-1:1;
	};
	virtual std::shared_ptr<Command> processline(std::string line);
};


#endif /* GERBERDECODER_H_ */

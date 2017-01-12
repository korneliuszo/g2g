/*
 * Decoder.h
 *
 *  Created on: May 29, 2016
 *      Author: kosa
 */

#ifndef DECODER_H_
#define DECODER_H_

#include "Command.h"
#include <string>

class Decoder
{
public:
	virtual ~Decoder() {};
	virtual std::shared_ptr<Command> processline(std::string line) = 0;
};




#endif /* DECODER_H_ */

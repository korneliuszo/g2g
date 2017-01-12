/*
 * Octagon.h
 *
 *  Created on: Feb 20, 2016
 *      Author: kosa
 */

#ifndef OCTAGON_H_
#define OCTAGON_H_

#include "Command.h"
#include "Poly.h"

class Octagon : public RegPoly
{
public:
	Octagon(double r): RegPoly(r,8,M_PI/8.0){};
};


#endif /* OCTAGON_H_ */

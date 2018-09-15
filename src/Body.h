/*
 * Body.h
 *
 *  Created on: Sep 5, 2018
 *      Author: julia
 */

#ifndef BODY_H_
#define BODY_H_

#include "Matrix.h"
#include "Constants.h"
#include "math.h"
#include "PositionCluster.h"
#include "Position.h"

namespace Body{

double toRadians(double degrees);

PositionCluster getLocalCornerPos(Position localBodyPos);
PositionCluster getGlobalCornerPos(Position localBodyPos, Position globalBodyPos);

PositionCluster getGlobalStepCenter(Position localBodyPos, Position globalBodyPos);

Position getGlobalCoMPos(Position localBodyPos, Position globalBodyPos);

Position getGlobalAdjustedCoMPos(Position localBodyPos, Position globalBodyPos, int corner);

Position getRelativeFootPos(Position globalCornerPos, Position globalFootPos);



}

#endif /* BODY_H_ */

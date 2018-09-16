/*
 * PositionCluster.h
 *
 *  Created on: Sep 7, 2018
 *      Author: julia
 */

#ifndef POSITIONCLUSTER_H_
#define POSITIONCLUSTER_H_

#include "Position.h"
//class Position;

class PositionCluster {
public:
	PositionCluster();
	PositionCluster(Position frontLeft, Position frontRight, Position rearLeft, Position rearRight);
	void copy(PositionCluster);
	virtual ~PositionCluster();

	//Position frontRight, frontLeft, rearRight, rearLeft;
	Position position[4];
};

#endif /* POSITIONCLUSTER_H_ */

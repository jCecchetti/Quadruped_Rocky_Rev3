/*
 * PositionCluster.cpp
 *
 *  Created on: Sep 7, 2018
 *      Author: julia
 */

#include "Position.h"
#include "PositionCluster.h"

PositionCluster::PositionCluster() {

}

PositionCluster::PositionCluster(Position frontRight, Position frontLeft, Position rearRight, Position rearLeft) {
	position[0] = frontLeft;
	position[1] = frontRight;
	position[2] = rearLeft;
	position[3] = rearRight;
}

void PositionCluster::copy(PositionCluster a){
	position[0].copy(a.position[0]);
	position[1].copy(a.position[1]);
	position[2].copy(a.position[2]);
	position[3].copy(a.position[3]);
}

PositionCluster::~PositionCluster() {
	// TODO Auto-generated destructor stub
}


/*
 * Body.cpp
 *
 *  Created on: Aug 4, 2018
 *      Author: julia
 */

#include "Body.h"

namespace Body{

double toRadians(double degrees){
	return degrees*0.0174533;
}

PositionCluster getLocalCornerPos(Position localBodyPos){
	PositionCluster localCornerPos;
	double tempLocalCornerPos [4][3] = {{Constants::BODYLENGTH/2, Constants::BODYWIDTH/2, 0},
									{Constants::BODYLENGTH/2, -Constants::BODYWIDTH/2, 0},
									{-Constants::BODYLENGTH/2, Constants::BODYWIDTH/2, 0},
									{-Constants::BODYLENGTH/2, -Constants::BODYWIDTH/2, 0}};

	double pitchRotationMatrix [3][3]= {{cos(toRadians(localBodyPos.pitch)), 0, -sin(toRadians(localBodyPos.pitch))},
									 {0, 1, 0},
									 {sin(toRadians(localBodyPos.pitch)), 0, cos(toRadians(localBodyPos.pitch))}};
	double rollRotationMatrix [3][3]= {{1, 0, 0},
									  {0, cos(toRadians(localBodyPos.roll)), sin(toRadians(localBodyPos.roll))},
									  {0, -sin(toRadians(localBodyPos.roll)), cos(toRadians(localBodyPos.roll))}};
	double yawRotationMatrix [3][3]= {{cos(toRadians(localBodyPos.yaw)), -sin(toRadians(localBodyPos.yaw)), 0},
								    {sin(toRadians(localBodyPos.yaw)), cos(toRadians(localBodyPos.yaw)), 0},
								    {0, 0, 1}};
	for(int i = 0; i < 4; i++){
		Matrix::multiply(rollRotationMatrix, tempLocalCornerPos[i], tempLocalCornerPos[i]);
		Matrix::multiply(pitchRotationMatrix, tempLocalCornerPos[i], tempLocalCornerPos[i]);
		Matrix::multiply(yawRotationMatrix, tempLocalCornerPos[i], tempLocalCornerPos[i]);
		localCornerPos.position[i].set(tempLocalCornerPos[i][0] + localBodyPos.x, tempLocalCornerPos[i][1] + localBodyPos.y,
				tempLocalCornerPos[i][2] + localBodyPos.z, localBodyPos.roll, localBodyPos.pitch, localBodyPos.yaw);

	}

	return localCornerPos;
}

PositionCluster getGlobalCornerPos(Position localBodyPos, Position globalBodyPos){
		PositionCluster globalCornerPos = getLocalCornerPos(localBodyPos);
		for(int i = 0; i < 4; i++){
			globalCornerPos.position[i].set(globalCornerPos.position[i].x + globalBodyPos.x, globalCornerPos.position[i].y + globalBodyPos.y,
					globalCornerPos.position[i].z + globalBodyPos.z, localBodyPos.roll, localBodyPos.pitch, localBodyPos.yaw);
		}
		return globalCornerPos;
}

PositionCluster getGlobalStepCenter(Position localBodyPos, Position globalBodyPos){
		PositionCluster globalStepCenter;
		double stepCenter[4][3] = {{Constants::BODYLENGTH/2, Constants::BODYWIDTH/2, 0},
				{Constants::BODYLENGTH/2, -Constants::BODYWIDTH/2, 0},
				{-Constants::BODYLENGTH/2, Constants::BODYWIDTH/2, 0},
				{-Constants::BODYLENGTH/2, -Constants::BODYWIDTH/2, 0}};

		double yawRotationMatrix[3][3] = {{cos(toRadians(localBodyPos.yaw)), -sin(toRadians(localBodyPos.yaw)), 0},
				{sin(toRadians(localBodyPos.yaw)), cos(toRadians(localBodyPos.yaw)), 0},
				{0, 0, 1}};

		for(int i = 0; i < 4; i++){
			Matrix::multiply(yawRotationMatrix, stepCenter[i], stepCenter[i]);
			globalStepCenter.position[i].set(stepCenter[i][0] + globalBodyPos.x, stepCenter[i][1] + globalBodyPos.y,
					stepCenter[i][2] + globalBodyPos.z, localBodyPos.roll, localBodyPos.pitch, localBodyPos.yaw);
		}

		return globalStepCenter;
	}

Position getGlobalCoMPos(Position localBodyPos, Position globalBodyPos){
		Position globalCoMPos(globalBodyPos.x + localBodyPos.x, globalBodyPos.y + localBodyPos.y, globalBodyPos.z + localBodyPos.z, 0, 0, 0);
		return globalCoMPos;
	}

Position getGlobalAdjustedCoMPos(Position localBodyPos, Position globalBodyPos, int corner){
	double localCoMBox[4][3] = {{Constants::COMBOX, Constants::COMBOX, 0},
											{Constants::COMBOX, -Constants::COMBOX, 0},
											{-Constants::COMBOX, Constants::COMBOX, 0},
											{-Constants::COMBOX, -Constants::COMBOX, 0}};

	double yawRotationMatrix[3][3]= {{cos(toRadians(localBodyPos.yaw)), -sin(toRadians(localBodyPos.yaw)), 0},
									    {sin(toRadians(localBodyPos.yaw)), cos(toRadians(localBodyPos.yaw)), 0},
									    {0, 0, 1}};

		Position globalCoMPos = getGlobalCoMPos(localBodyPos, globalBodyPos);

		double adjustedCoMPos[3];
		Matrix::multiply(yawRotationMatrix, localCoMBox[corner], adjustedCoMPos);//get position of adjusted CoM opposite of the stepping leg
		return Position(adjustedCoMPos[0] + globalCoMPos.x, adjustedCoMPos[1] + globalCoMPos.y, 0, 0, 0, 0);
	}

Position getRelativeFootPos(Position globalCornerPos, Position globalFootPos){

		double unrotatedLocalFootPos[3] = {globalFootPos.x - globalCornerPos.x, globalFootPos.y - globalCornerPos.y, globalFootPos.z - globalCornerPos.z};

		double rollRotationMatrix[3][3] = {{1, 0, 0},
				  {0, cos(toRadians(-globalCornerPos.roll)), sin(toRadians(-globalCornerPos.roll))},
				  {0, -sin(toRadians(-globalCornerPos.roll)), cos(toRadians(-globalCornerPos.roll))}};
		double pitchRotationMatrix[3][3] = {{cos(toRadians(-globalCornerPos.pitch)), 0, -sin(toRadians(-globalCornerPos.pitch))},
				 {0, 1, 0},
				 {sin(toRadians(-globalCornerPos.pitch)), 0, cos(toRadians(-globalCornerPos.pitch))}};
		double yawRotationMatrix[3][3] = {{cos(toRadians(-globalCornerPos.yaw)), -sin(toRadians(-globalCornerPos.yaw)), 0},
			    {sin(toRadians(-globalCornerPos.yaw)), cos(toRadians(-globalCornerPos.yaw)), 0},
			    {0, 0, 1}};

		Matrix::multiply(rollRotationMatrix, unrotatedLocalFootPos, unrotatedLocalFootPos);
		Matrix::multiply(pitchRotationMatrix, unrotatedLocalFootPos, unrotatedLocalFootPos);
		Matrix::multiply(yawRotationMatrix, unrotatedLocalFootPos, unrotatedLocalFootPos);


		Position relativeFootPos(unrotatedLocalFootPos[0], unrotatedLocalFootPos[1], unrotatedLocalFootPos[2],0,0,0);

		return relativeFootPos;
	}



}

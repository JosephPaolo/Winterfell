#pragma once

#include "GameObject.h"
#include "BRDataTypes.h"
#include <SFML/Graphics.hpp>

using namespace BlueRapsolEnums;

class PhysicsSystem {

public:
	PhysicsSystem(); //constructor

	void UpdatePhysics(); //Called in the game loop per tick.
	void UpdatePhysics(const std::vector<std::unique_ptr<GameObject>>& getObjRef); //Called in the game loop per tick. Receives access to GameObject array.
	bool TestAABBOverlap(AABB* a, AABB* b);
	
private: 
	void DeflectObj(PhysicsComponent* physComponentRef, AxisType collisionType);

};
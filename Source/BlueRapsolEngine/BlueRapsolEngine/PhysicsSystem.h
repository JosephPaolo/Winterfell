#pragma once

#include "GameObject.h"
#include "BRDataTypes.h"
#include <SFML/Graphics.hpp>

class PhysicsSystem {

public:
	PhysicsSystem(); //constructor

	void UpdatePhysics(); //Called in the game loop per tick.
	void UpdatePhysics(const std::vector<std::unique_ptr<GameObject>>& getObjRef); //Called in the game loop per tick. Receives access to GameObject array.
	bool TestAABBOverlap(AABB* a, AABB* b);
	//void DeflectObj(const std::unique_ptr<GameObject>& getObjRef, bool isVerticalward);
	
	
private: 
	void DeflectObj(PhysicsComponent* physComponentRef, BRAxisType::AxisType collisionType);

};
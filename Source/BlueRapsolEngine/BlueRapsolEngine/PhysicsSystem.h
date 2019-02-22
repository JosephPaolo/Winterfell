#pragma once

#include "GameObject.h"
#include "BRDataTypes.h"
#include <SFML/Graphics.hpp>

class PhysicsSystem {

public:
	PhysicsSystem(); //constructor

	void UpdatePhysics(); //Called in the game loop per tick.
	void UpdatePhysics(const std::vector<std::unique_ptr<GameObject>>& getObjRef); //Called in the game loop per tick. Receives access to GameObject array.

private: 

	//Things to do for milestone 1 (Minimum requirements):
	//- AABB collision detection
	//- Collision resolution
};
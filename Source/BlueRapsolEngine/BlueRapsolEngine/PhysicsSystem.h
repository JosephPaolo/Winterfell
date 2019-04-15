#pragma once

#include "GameObject.h"
#include "BRDataTypes.h"
#include <SFML/Graphics.hpp>

using namespace BlueRapsolEnums;

class PhysicsSystem {

public:
	PhysicsSystem(); //constructor

	void UpdatePhysics(); //Called in the game loop per tick.
	void UpdatePhysics(const std::vector<std::unique_ptr<GameObject>>& getObjRef, int player1Index, int player2Index, float deltaTime); //Called in the game loop per tick. Receives access to GameObject array.
	bool TestAABBOverlap(AABB* a, AABB* b);
	
private: 
	void DeflectObj(PhysicsComponent* physComponentRef, AxisType collisionType);

	std::wstring msg;

	sf::Vector2f newPosition;

	Vector2 playerVelocityHolder;
	Vector2 objVelocityHolder;
	Vector2 bulletVelocityHolder;
	Vector2 hazardVelocityHolder;

	BRDataType::AABB playerBounds;
	BRDataType::AABB wallBounds;
	BRDataType::AABB bulletBounds;
	BRDataType::AABB hazardBounds;

	float widthHolder;
	float heightHolder;
	float collisionPadding = 1; //must be higher than velocity value to work
	float hazardPadding = 1; //must be higher than velocity value to work
	int startingIndexA = 0;
	int startingIndexB = 1;

};
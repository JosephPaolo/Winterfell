#pragma once

#include "BaseComponent.h"
#include "BRDataTypes.h"

using namespace BRDataType;

class PhysicsComponent : public BaseComponent {

public:
	PhysicsComponent();

	Vector2 velocity;

	void SetVelocity(Vector2 newVelocity);
	void SetVelocity(float newX, float newY);
	Vector2 GetVelocity();

	//Things to do: 
	//- Add collider bounds

};
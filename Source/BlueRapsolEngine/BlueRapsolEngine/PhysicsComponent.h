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
	AABB GetBounds();
	void SetBounds(Vector2 newMin, Vector2 newMax);

	//Things to do: 
	//- Add collider bounds

private:
	AABB bounds; //Axis-Aligned Bounding Box

};
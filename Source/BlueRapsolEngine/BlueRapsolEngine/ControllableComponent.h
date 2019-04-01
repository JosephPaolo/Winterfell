#pragma once

#include "BaseComponent.h"
#include "PhysicsComponent.h"
#include "BREnums.h"

class ControllableComponent : BaseComponent {

public:

	void Move(CardinalDirection direction, PhysicsComponent* physicsRef);

	void Stop(PhysicsComponent* physicsRef);

	void Fire();

	
};
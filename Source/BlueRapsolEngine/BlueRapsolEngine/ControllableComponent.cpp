#include "ControllableComponent.h"

using namespace BlueRapsolEnums;

void ControllableComponent::Move(CardinalDirection direction, PhysicsComponent* physicsRef) {

	if (!physicsRef) {
		return;
	}

	if (direction == CardinalDirection::North) {
		physicsRef->SetVelocity(0,-1);
	}
	else if (direction == CardinalDirection::South) {
		physicsRef->SetVelocity(0, 1);
	}
	else if (direction == CardinalDirection::East) {
		physicsRef->SetVelocity(1, 0);
	}
	else if (direction == CardinalDirection::West) {
		physicsRef->SetVelocity(-1, 0);
	}
}

void ControllableComponent::Fire() {

}

void ControllableComponent::Stop(PhysicsComponent* physicsRef) {
	physicsRef->SetVelocity(0, 0);
}
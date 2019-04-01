#include "PhysicsComponent.h"

using namespace BlueRapsolEnums;

PhysicsComponent::PhysicsComponent() {
	type = Physics;
	velocity.x = 0;
	velocity.y = 0;
}

void PhysicsComponent::SetVelocity(Vector2 newVelocity) {
	velocity = newVelocity;
}

void PhysicsComponent::SetVelocity(float newX, float newY) {
	velocity.x = newX; velocity.y = newY;
}

Vector2 PhysicsComponent::GetVelocity() {
	return velocity;
}

AABB PhysicsComponent::GetBounds() {
	return bounds;
}

void PhysicsComponent::SetBounds(Vector2 newMin, Vector2 newMax) {
	bounds.min = newMin;
	bounds.max = newMax;
}
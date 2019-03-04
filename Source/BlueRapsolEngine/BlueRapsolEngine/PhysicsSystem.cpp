#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem() {

}

void PhysicsSystem::UpdatePhysics() {

}

void PhysicsSystem::UpdatePhysics(const std::vector<std::unique_ptr<GameObject>>& getObjRef) {

	sf::Vector2f newPosition;

	//Loops through Objects and change their position based on velocity. We just add velocity to position.
	for (auto& obj : getObjRef) {
		newPosition.x = obj.get()->GetTransformComponent()->GetPosition().x + obj.get()->GetPhysicsComponent()->GetVelocity().x;
		newPosition.y = obj.get()->GetTransformComponent()->GetPosition().y + obj.get()->GetPhysicsComponent()->GetVelocity().y;
		obj.get()->GetTransformComponent()->SetPosition(newPosition);
	}

}

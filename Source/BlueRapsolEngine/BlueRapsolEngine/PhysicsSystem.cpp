#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem() {

}

void PhysicsSystem::UpdatePhysics() {

}

void PhysicsSystem::UpdatePhysics(const std::vector<std::unique_ptr<GameObject>>& getObjRef) {

	sf::Vector2f newPosition;

	//Check Collision and resolve them
	//for (auto& objA : getObjRef) {
	//	for (auto& objB : getObjRef) {
	//		if (TestAABBOverlap(&objA.get()->GetPhysicsComponent()->GetBounds(), &objB.get()->GetPhysicsComponent()->GetBounds())) {
	//			DeflectObj(objA.get()->GetPhysicsComponent(), true); //TODO figure out the direction of collision
	//			DeflectObj(objB.get()->GetPhysicsComponent(), true);
	//		}
	//	}
	//}

	//Loops through Objects and change their position based on velocity. We just add velocity to position.
	for (auto& obj : getObjRef) {
		newPosition.x = obj.get()->GetTransformComponent()->GetPosition().x + obj.get()->GetPhysicsComponent()->GetVelocity().x;
		newPosition.y = obj.get()->GetTransformComponent()->GetPosition().y + obj.get()->GetPhysicsComponent()->GetVelocity().y;
		obj.get()->GetTransformComponent()->SetPosition(newPosition);
	}

}

//check if object bounds collide
bool PhysicsSystem::TestAABBOverlap(AABB* a, AABB* b) {
	float d1x = b->min.x - a->max.x;
	float d1y = b->min.y - a->max.y;
	float d2x = a->min.x - b->max.x;
	float d2y = a->min.y - b->max.y;
	if (d1x > 0.0f || d1y > 0.0f)
		return FALSE;
	if (d2x > 0.0f || d2y > 0.0f)
		return FALSE;
	return TRUE;
}

//Change object velocity to simulate deflection upon collision
void PhysicsSystem::DeflectObj(PhysicsComponent* physComponentRef, bool isVerticalward) {

	if (isVerticalward) {
		physComponentRef->SetVelocity(physComponentRef->GetVelocity().x * -1, physComponentRef->GetVelocity().y);
	}
	else {
		physComponentRef->SetVelocity(physComponentRef->GetVelocity().x, physComponentRef->GetVelocity().y * -1);
	}

}

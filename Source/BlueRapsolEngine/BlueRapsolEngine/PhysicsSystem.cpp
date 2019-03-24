#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem() {

}

void PhysicsSystem::UpdatePhysics() {

}

//TODO: figure out why Diameter is divided by 4 instead of 2 when the size of the shape is 50x50
void PhysicsSystem::UpdatePhysics(const std::vector<std::unique_ptr<GameObject>>& getObjRef) {
	std::wstring msg;

	sf::Vector2f newPosition;

	BRDataType::AABB boundsWorldPosA;
	BRDataType::AABB boundsWorldPosB;
	float widthHolder;
	float heightHolder;
	float collisionPadding = 1; //must be higher than velocity value to work
	int startingIndexA = 0;
	int startingIndexB = 1;


	for (int ia = startingIndexA; ia < getObjRef.size(); ia++) {
		for (int ib = startingIndexB; ib < getObjRef.size(); ib++) {

			//halfDiameterX = abs(getObjRef[ia].get()->GetPhysicsComponent()->GetBounds().min.x - getObjRef[ia].get()->GetPhysicsComponent()->GetBounds().max.x) / 4;
			//halfDiameterY = abs(getObjRef[ia].get()->GetPhysicsComponent()->GetBounds().min.y - getObjRef[ia].get()->GetPhysicsComponent()->GetBounds().max.y) / 4;

			widthHolder = abs(getObjRef[ia].get()->GetPhysicsComponent()->GetBounds().min.x - getObjRef[ia].get()->GetPhysicsComponent()->GetBounds().max.x) / 2;
			heightHolder = abs(getObjRef[ia].get()->GetPhysicsComponent()->GetBounds().min.y - getObjRef[ia].get()->GetPhysicsComponent()->GetBounds().max.y) / 2;

			//Note: The origin of a shape is its top left corner.
			boundsWorldPosA.min.x = getObjRef[ia].get()->GetTransformComponent()->GetPosition().x;
			boundsWorldPosA.max.x = getObjRef[ia].get()->GetTransformComponent()->GetPosition().x + widthHolder;
			boundsWorldPosA.min.y = getObjRef[ia].get()->GetTransformComponent()->GetPosition().y + heightHolder; //Note: Remember, In this case Y positive is downwards
			boundsWorldPosA.max.y = getObjRef[ia].get()->GetTransformComponent()->GetPosition().y; //and Y negative is upwards

			//halfDiameterX = abs(getObjRef[ib].get()->GetPhysicsComponent()->GetBounds().min.x - getObjRef[ib].get()->GetPhysicsComponent()->GetBounds().max.x) / 4;
			//halfDiameterY = abs(getObjRef[ib].get()->GetPhysicsComponent()->GetBounds().min.y - getObjRef[ib].get()->GetPhysicsComponent()->GetBounds().max.y) / 4;

			widthHolder = abs(getObjRef[ib].get()->GetPhysicsComponent()->GetBounds().min.x - getObjRef[ib].get()->GetPhysicsComponent()->GetBounds().max.x) / 2;
			heightHolder = abs(getObjRef[ib].get()->GetPhysicsComponent()->GetBounds().min.y - getObjRef[ib].get()->GetPhysicsComponent()->GetBounds().max.y) / 2;

			//Note: The origin of a shape is its top left corner.
			boundsWorldPosB.min.x = getObjRef[ib].get()->GetTransformComponent()->GetPosition().x;
			boundsWorldPosB.max.x = getObjRef[ib].get()->GetTransformComponent()->GetPosition().x + widthHolder;
			boundsWorldPosB.min.y = getObjRef[ib].get()->GetTransformComponent()->GetPosition().y + heightHolder; //Note: Remember, In this case Y positive is downwards
			boundsWorldPosB.max.y = getObjRef[ib].get()->GetTransformComponent()->GetPosition().y; //and Y negative is upwards

			//Check if there is overlap and that at least one of the pair is moving velocity wise
			if (TestAABBOverlap(&boundsWorldPosA, &boundsWorldPosB)
				&& !(getObjRef[ia].get()->GetPhysicsComponent()->GetVelocity().x == 0 
				&& getObjRef[ia].get()->GetPhysicsComponent()->GetVelocity().y == 0 
				&& getObjRef[ib].get()->GetPhysicsComponent()->GetVelocity().x == 0 
				&& getObjRef[ib].get()->GetPhysicsComponent()->GetVelocity().y == 0) ) {

				//Determine the direction of collision based on x and y position differences. 
				if ( (boundsWorldPosA.max.x > boundsWorldPosB.min.x) && (boundsWorldPosA.max.x < boundsWorldPosB.min.x + collisionPadding) ) { // A collides with B from left
					//OutputDebugString(L"[Notice] Horiontal Collision detected.\n");
					DeflectObj(getObjRef[ia].get()->GetPhysicsComponent(), BRAxisType::AxisType::Horizontal);
					DeflectObj(getObjRef[ib].get()->GetPhysicsComponent(), BRAxisType::AxisType::Horizontal);
				}
				else if ( (boundsWorldPosA.min.x < boundsWorldPosB.max.x) && (boundsWorldPosA.min.x > boundsWorldPosB.max.x - collisionPadding)) { // A collides with B from the right
					//OutputDebugString(L"[Notice] Horiontal Collision detected.\n");
					DeflectObj(getObjRef[ia].get()->GetPhysicsComponent(), BRAxisType::AxisType::Horizontal);
					DeflectObj(getObjRef[ib].get()->GetPhysicsComponent(), BRAxisType::AxisType::Horizontal);
				}
				else if ( (boundsWorldPosA.max.y < boundsWorldPosB.min.y) && (boundsWorldPosA.max.y > boundsWorldPosB.min.y - collisionPadding) ) { // A collides with B from below
					//OutputDebugString(L"[Notice] Vertical Collision detected.\n");
					DeflectObj(getObjRef[ia].get()->GetPhysicsComponent(), BRAxisType::AxisType::Vertical);
					DeflectObj(getObjRef[ib].get()->GetPhysicsComponent(), BRAxisType::AxisType::Vertical);
				}
				else if ( (boundsWorldPosA.min.y > boundsWorldPosB.max.y) && (boundsWorldPosA.min.y < boundsWorldPosB.max.y + collisionPadding) ) { // A collides with B from above
					//OutputDebugString(L"[Notice] Vertical Collision detected.\n");
					DeflectObj(getObjRef[ia].get()->GetPhysicsComponent(), BRAxisType::AxisType::Vertical);
					DeflectObj(getObjRef[ib].get()->GetPhysicsComponent(), BRAxisType::AxisType::Vertical);
				}
				//else if ( (getObjRef[ia].get()->GetPhysicsComponent()->GetVelocity().x == getObjRef[ia].get()->GetPhysicsComponent()->GetVelocity().y) 
				//	   && (getObjRef[ib].get()->GetPhysicsComponent()->GetVelocity().x == getObjRef[ib].get()->GetPhysicsComponent()->GetVelocity().y) ) { //A collides with B diagonally
				//	OutputDebugString(L"[Notice] Diagonal Collision detected.\n");
				//	DeflectObj(getObjRef[ia].get()->GetPhysicsComponent(), BRAxisType::AxisType::Diagonal);
				//}
			}
		}
		startingIndexA++;
		startingIndexB = startingIndexA + 1;
	}

	//Loops through Objects and change their position based on velocity. We just add velocity to position.
	for (auto& obj : getObjRef) {
		newPosition.x = obj.get()->GetTransformComponent()->GetPosition().x + obj.get()->GetPhysicsComponent()->GetVelocity().x;
		newPosition.y = obj.get()->GetTransformComponent()->GetPosition().y + obj.get()->GetPhysicsComponent()->GetVelocity().y;
		obj.get()->GetTransformComponent()->SetPosition(newPosition);
	}

}

//check if object bounds collide
//Note: In this case the origin is at the top left of the screen, rightward is x positive, downward is y positive.
bool PhysicsSystem::TestAABBOverlap(AABB* a, AABB* b) {

	if ( (a->max.x > b->min.x && a->max.x <= b->max.x) || (a->min.x < b->max.x && a->min.x >= b->min.x) ) { //Check Horizontal overlap
		//OutputDebugString(L"[Notice] Horiontal Overlap detected.\n");

		if ( (a->max.y < b->min.y && a->max.y >= b->max.y) || (a->min.y > b->max.y && a->min.y <= b->min.y)) { //Check Vertical overlap. Note: Remember, In this case Y positive is downwards and Y negative is upwards
			//OutputDebugString(L"[Notice] Vertical Overlap detected.\n");
			return TRUE;
		}
	}

	return FALSE;
}

//Change object velocity to simulate deflection upon collision
void PhysicsSystem::DeflectObj(PhysicsComponent* physComponentRef, BRAxisType::AxisType collisionType) {
	//Note: deflecting an object with(0, 0) velocity will not apply changes because anything multiplied by 0 is 0.

	if (collisionType == BRAxisType::Diagonal) { //Diagonal
		physComponentRef->SetVelocity(physComponentRef->GetVelocity().x * -1, physComponentRef->GetVelocity().y * -1);
	}
	else if (collisionType == BRAxisType::Vertical) { //Vertical
		physComponentRef->SetVelocity(physComponentRef->GetVelocity().x, physComponentRef->GetVelocity().y * -1);
	}
	else if (collisionType == BRAxisType::Horizontal) { //Horizontal
		physComponentRef->SetVelocity(physComponentRef->GetVelocity().x * -1, physComponentRef->GetVelocity().y);
	}
}

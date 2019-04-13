#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem() {

}

void PhysicsSystem::UpdatePhysics() {

}

//TODO: Diameter is divided by 4 instead of 2 because apparently shape size in pixels differ in measurement from scene positions
void PhysicsSystem::UpdatePhysics(const std::vector<std::unique_ptr<GameObject>>& getObjRef, int player1Index, int player2Index) {
	std::wstring msg;

	sf::Vector2f newPosition;
	/*Vector2 velocityHolderA;
	Vector2 velocityHolderB;*/

	Vector2 playerVelocityHolder;
	Vector2 wallVelocityHolder;

	/*BRDataType::AABB boundsWorldPosA;
	BRDataType::AABB boundsWorldPosB;*/

	BRDataType::AABB playerBounds;
	BRDataType::AABB wallBounds;

	float widthHolder;
	float heightHolder;
	float collisionPadding = 1; //must be higher than velocity value to work
	int startingIndexA = 0;
	int startingIndexB = 1;

	//Only compare players to walls
	//TODO change index from starting at 2 when player index will be variable in the future
	for (int i = 2; i < getObjRef.size(); i++) {

		//Skip object if it's not a wall
		if (getObjRef[i].get()->isWall == true) {

			//Establish wall bounds and velocity
			widthHolder = abs(getObjRef[i].get()->GetPhysicsComponent()->GetBounds().min.x - getObjRef[i].get()->GetPhysicsComponent()->GetBounds().max.x) / 2;
			heightHolder = abs(getObjRef[i].get()->GetPhysicsComponent()->GetBounds().min.y - getObjRef[i].get()->GetPhysicsComponent()->GetBounds().max.y) / 2;

			wallBounds.min.x = getObjRef[i].get()->GetTransformComponent()->GetPosition().x;
			wallBounds.max.x = getObjRef[i].get()->GetTransformComponent()->GetPosition().x + widthHolder;
			wallBounds.min.y = getObjRef[i].get()->GetTransformComponent()->GetPosition().y + heightHolder; //Note: Remember, In this case Y positive is downwards
			wallBounds.max.y = getObjRef[i].get()->GetTransformComponent()->GetPosition().y; //and Y negative is upwards

			wallVelocityHolder.x = getObjRef[i].get()->GetPhysicsComponent()->GetVelocity().x;
			wallVelocityHolder.y = getObjRef[i].get()->GetPhysicsComponent()->GetVelocity().y;

			//Test player 1
			widthHolder = abs(getObjRef[0].get()->GetPhysicsComponent()->GetBounds().min.x - getObjRef[0].get()->GetPhysicsComponent()->GetBounds().max.x) / 2;
			heightHolder = abs(getObjRef[0].get()->GetPhysicsComponent()->GetBounds().min.y - getObjRef[0].get()->GetPhysicsComponent()->GetBounds().max.y) / 2;

			playerBounds.min.x = getObjRef[0].get()->GetTransformComponent()->GetPosition().x;
			playerBounds.max.x = getObjRef[0].get()->GetTransformComponent()->GetPosition().x + widthHolder;
			playerBounds.min.y = getObjRef[0].get()->GetTransformComponent()->GetPosition().y + heightHolder; //Note: Remember, In this case Y positive is downwards
			playerBounds.max.y = getObjRef[0].get()->GetTransformComponent()->GetPosition().y; //and Y negative is upwards

			playerVelocityHolder.x = getObjRef[0].get()->GetPhysicsComponent()->GetVelocity().x;
			playerVelocityHolder.y = getObjRef[0].get()->GetPhysicsComponent()->GetVelocity().y;

			//Check if there is overlap and that player 1 is moving velocity wise
			if (TestAABBOverlap(&playerBounds, &wallBounds)
				&& !(playerVelocityHolder.x == 0 && playerVelocityHolder.y == 0)) {

				//Prevent going further upon collision
				if ((playerBounds.max.x > wallBounds.min.x) && (playerBounds.max.x < wallBounds.min.x + collisionPadding)) { // Player collides with Wall from left
					OutputDebugString(L"[Notice] Player 1 collides with Wall from left.\n");
					if (playerVelocityHolder.x > 0) { //prevent player 1 from moving further
						getObjRef[0].get()->GetPhysicsComponent()->SetVelocity(0, playerVelocityHolder.y);
					}
					//else allow current velocity
				}
				else if ((playerBounds.min.x < wallBounds.max.x) && (playerBounds.min.x > wallBounds.max.x - collisionPadding)) { // Player collides with Wall from right
					OutputDebugString(L"[Notice] Player 1 collides with Wall from right.\n");
					if (playerVelocityHolder.x < 0) { //prevent player 1 from moving further
						getObjRef[0].get()->GetPhysicsComponent()->SetVelocity(0, playerVelocityHolder.y);
					}
					//else allow current velocity
				}
				else if ((playerBounds.max.y < wallBounds.min.y) && (playerBounds.max.y > wallBounds.min.y - collisionPadding)) { // Player collides with Wall from below
					OutputDebugString(L"[Notice] Player 1 collides with Wall from below.\n");
					if (playerVelocityHolder.y < 0) { //prevent player 1 from moving further
						getObjRef[0].get()->GetPhysicsComponent()->SetVelocity(playerVelocityHolder.x, 0);
					}
					//else allow current velocity
				}
				else if ((playerBounds.min.y > wallBounds.max.y) && (playerBounds.min.y < wallBounds.max.y + collisionPadding)) { // Player collides with Wall from above
					OutputDebugString(L"[Notice] Player 1 collides with Wall from above.\n");
					if (playerVelocityHolder.y > 0) { //prevent player 1 from moving further
						getObjRef[0].get()->GetPhysicsComponent()->SetVelocity(playerVelocityHolder.x, 0);
					}
					//else allow current velocity
				}
			}

			//Test player 2
			widthHolder = abs(getObjRef[1].get()->GetPhysicsComponent()->GetBounds().min.x - getObjRef[1].get()->GetPhysicsComponent()->GetBounds().max.x) / 2;
			heightHolder = abs(getObjRef[1].get()->GetPhysicsComponent()->GetBounds().min.y - getObjRef[1].get()->GetPhysicsComponent()->GetBounds().max.y) / 2;

			playerBounds.min.x = getObjRef[1].get()->GetTransformComponent()->GetPosition().x;
			playerBounds.max.x = getObjRef[1].get()->GetTransformComponent()->GetPosition().x + widthHolder;
			playerBounds.min.y = getObjRef[1].get()->GetTransformComponent()->GetPosition().y + heightHolder; //Note: Remember, In this case Y positive is downwards
			playerBounds.max.y = getObjRef[1].get()->GetTransformComponent()->GetPosition().y; //and Y negative is upwards

			playerVelocityHolder.x = getObjRef[1].get()->GetPhysicsComponent()->GetVelocity().x;
			playerVelocityHolder.y = getObjRef[1].get()->GetPhysicsComponent()->GetVelocity().y;

			//Check if there is overlap and that player 2 is moving velocity wise
			if (TestAABBOverlap(&playerBounds, &wallBounds)
				&& !(playerVelocityHolder.x == 0 && playerVelocityHolder.y == 0)) {

				//Prevent going further upon collision
				if ((playerBounds.max.x > wallBounds.min.x) && (playerBounds.max.x < wallBounds.min.x + collisionPadding)) { // Player collides with Wall from left
					OutputDebugString(L"[Notice] Horiontal Collision detected.\n");
					if (playerVelocityHolder.x > 0) { //prevent player 1 from moving further
						getObjRef[1].get()->GetPhysicsComponent()->SetVelocity(0, playerVelocityHolder.y);
					}
					//else allow current velocity
				}
				else if ((playerBounds.min.x < wallBounds.max.x) && (playerBounds.min.x > wallBounds.max.x - collisionPadding)) { // Player collides with Wall from right
					OutputDebugString(L"[Notice] Horiontal Collision detected.\n");
					if (playerVelocityHolder.x < 0) { //prevent player 1 from moving further
						getObjRef[1].get()->GetPhysicsComponent()->SetVelocity(0, playerVelocityHolder.y);
					}
					//else allow current velocity
				}
				else if ((playerBounds.max.y < wallBounds.min.y) && (playerBounds.max.y > wallBounds.min.y - collisionPadding)) { // Player collides with Wall from below
					OutputDebugString(L"[Notice] Vertical Collision detected.\n");
					if (playerVelocityHolder.y < 0) { //prevent player 1 from moving further
						getObjRef[1].get()->GetPhysicsComponent()->SetVelocity(playerVelocityHolder.x, 0);
					}
					//else allow current velocity
				}
				else if ((playerBounds.min.y > wallBounds.max.y) && (playerBounds.min.y < wallBounds.max.y + collisionPadding)) { // Player collides with Wall from above
					OutputDebugString(L"[Notice] Vertical Collision detected.\n");
					if (playerVelocityHolder.y > 0) { //prevent player 1 from moving further
						getObjRef[1].get()->GetPhysicsComponent()->SetVelocity(playerVelocityHolder.x, 0);
					}
					//else allow current velocity
				}
			}
		}

	}

	//for (int ia = startingIndexA; ia < getObjRef.size(); ia++) {
	//	for (int ib = startingIndexB; ib < getObjRef.size(); ib++) {

	//		//halfDiameterX = abs(getObjRef[ia].get()->GetPhysicsComponent()->GetBounds().min.x - getObjRef[ia].get()->GetPhysicsComponent()->GetBounds().max.x) / 4;
	//		//halfDiameterY = abs(getObjRef[ia].get()->GetPhysicsComponent()->GetBounds().min.y - getObjRef[ia].get()->GetPhysicsComponent()->GetBounds().max.y) / 4;

	//		widthHolder = abs(getObjRef[ia].get()->GetPhysicsComponent()->GetBounds().min.x - getObjRef[ia].get()->GetPhysicsComponent()->GetBounds().max.x) / 2;
	//		heightHolder = abs(getObjRef[ia].get()->GetPhysicsComponent()->GetBounds().min.y - getObjRef[ia].get()->GetPhysicsComponent()->GetBounds().max.y) / 2;

	//		//Note: The origin of a shape is its top left corner.
	//		boundsWorldPosA.min.x = getObjRef[ia].get()->GetTransformComponent()->GetPosition().x;
	//		boundsWorldPosA.max.x = getObjRef[ia].get()->GetTransformComponent()->GetPosition().x + widthHolder;
	//		boundsWorldPosA.min.y = getObjRef[ia].get()->GetTransformComponent()->GetPosition().y + heightHolder; //Note: Remember, In this case Y positive is downwards
	//		boundsWorldPosA.max.y = getObjRef[ia].get()->GetTransformComponent()->GetPosition().y; //and Y negative is upwards

	//		//halfDiameterX = abs(getObjRef[ib].get()->GetPhysicsComponent()->GetBounds().min.x - getObjRef[ib].get()->GetPhysicsComponent()->GetBounds().max.x) / 4;
	//		//halfDiameterY = abs(getObjRef[ib].get()->GetPhysicsComponent()->GetBounds().min.y - getObjRef[ib].get()->GetPhysicsComponent()->GetBounds().max.y) / 4;

	//		widthHolder = abs(getObjRef[ib].get()->GetPhysicsComponent()->GetBounds().min.x - getObjRef[ib].get()->GetPhysicsComponent()->GetBounds().max.x) / 2;
	//		heightHolder = abs(getObjRef[ib].get()->GetPhysicsComponent()->GetBounds().min.y - getObjRef[ib].get()->GetPhysicsComponent()->GetBounds().max.y) / 2;

	//		//Note: The origin of a shape is its top left corner.
	//		boundsWorldPosB.min.x = getObjRef[ib].get()->GetTransformComponent()->GetPosition().x;
	//		boundsWorldPosB.max.x = getObjRef[ib].get()->GetTransformComponent()->GetPosition().x + widthHolder;
	//		boundsWorldPosB.min.y = getObjRef[ib].get()->GetTransformComponent()->GetPosition().y + heightHolder; //Note: Remember, In this case Y positive is downwards
	//		boundsWorldPosB.max.y = getObjRef[ib].get()->GetTransformComponent()->GetPosition().y; //and Y negative is upwards

	//		velocityHolderA.x = getObjRef[ia].get()->GetPhysicsComponent()->GetVelocity().x;
	//		velocityHolderA.y = getObjRef[ia].get()->GetPhysicsComponent()->GetVelocity().y;
	//		velocityHolderB.x = getObjRef[ib].get()->GetPhysicsComponent()->GetVelocity().x;
	//		velocityHolderB.y = getObjRef[ib].get()->GetPhysicsComponent()->GetVelocity().y;

	//		//Check if there is overlap and that at least one of the pair is moving velocity wise
	//		if (TestAABBOverlap(&boundsWorldPosA, &boundsWorldPosB)
	//			&& !(velocityHolderA.x == 0
	//			&& velocityHolderA.y == 0
	//			&& velocityHolderB.x == 0
	//			&& velocityHolderB.y == 0) ) {

	//			//Prevent going further upon collision

	//			if ((boundsWorldPosA.max.x > boundsWorldPosB.min.x) && (boundsWorldPosA.max.x < boundsWorldPosB.min.x + collisionPadding)) { // A collides with B from left
	//				//OutputDebugString(L"[Notice] Horiontal Collision detected.\n");

	//				//if player is A prevent it from moving further
	//				if (getObjRef[ia].get()->isPlayer && velocityHolderA.x > 0) {
	//					getObjRef[ia].get()->GetPhysicsComponent()->SetVelocity(0, velocityHolderA.y);
	//				}
	//				else if (!getObjRef[ia].get()->isPlayer) { //Deflect if not player
	//					DeflectObj(getObjRef[ia].get()->GetPhysicsComponent(), AxisType::Horizontal);
	//				}
	//				//else allow current velocity

	//				//if player is B prevent it from moving further
	//				if (getObjRef[ib].get()->isPlayer && velocityHolderB.x < 0) {
	//					getObjRef[ib].get()->GetPhysicsComponent()->SetVelocity(0, velocityHolderB.y);
	//				}
	//				else if (!getObjRef[ib].get()->isPlayer) { //Deflect if not player
	//					DeflectObj(getObjRef[ib].get()->GetPhysicsComponent(), AxisType::Horizontal);
	//				}
	//				//else allow current velocity

	//			}
	//			else if ((boundsWorldPosA.min.x < boundsWorldPosB.max.x) && (boundsWorldPosA.min.x > boundsWorldPosB.max.x - collisionPadding)) { // A collides with B from the right
	//				//OutputDebugString(L"[Notice] Horiontal Collision detected.\n");

	//				//if player is A prevent it from moving further
	//				if (getObjRef[ia].get()->isPlayer && velocityHolderA.x < 0) {
	//					getObjRef[ia].get()->GetPhysicsComponent()->SetVelocity(0, velocityHolderA.y);
	//				}
	//				else if (!getObjRef[ia].get()->isPlayer) { //Deflect if not player
	//					DeflectObj(getObjRef[ia].get()->GetPhysicsComponent(), AxisType::Horizontal);
	//				}
	//				//else allow current velocity

	//				//if player is B prevent it from moving further
	//				if (getObjRef[ib].get()->isPlayer && velocityHolderB.x > 0) {
	//					getObjRef[ib].get()->GetPhysicsComponent()->SetVelocity(0, velocityHolderB.y);
	//				}
	//				else if (!getObjRef[ib].get()->isPlayer) { //Deflect if not player
	//					DeflectObj(getObjRef[ib].get()->GetPhysicsComponent(), AxisType::Horizontal);
	//				}
	//				//else allow current velocity
	//			}
	//			else if ((boundsWorldPosA.max.y < boundsWorldPosB.min.y) && (boundsWorldPosA.max.y > boundsWorldPosB.min.y - collisionPadding)) { // A collides with B from below
	//				//OutputDebugString(L"[Notice] Vertical Collision detected.\n");

	//				//if player is A prevent it from moving further
	//				if (getObjRef[ia].get()->isPlayer && velocityHolderA.y < 0) {
	//					getObjRef[ia].get()->GetPhysicsComponent()->SetVelocity(velocityHolderA.x, 0);
	//				}
	//				else if (!getObjRef[ia].get()->isPlayer) { //Deflect if not player
	//					DeflectObj(getObjRef[ia].get()->GetPhysicsComponent(), AxisType::Vertical);
	//				}
	//				//else allow current velocity

	//				//if player is B prevent it from moving further
	//				if (getObjRef[ib].get()->isPlayer && velocityHolderB.y > 0) {
	//					getObjRef[ib].get()->GetPhysicsComponent()->SetVelocity(velocityHolderA.x, 0);
	//				}
	//				else if (!getObjRef[ib].get()->isPlayer) { //Deflect if not player
	//					DeflectObj(getObjRef[ib].get()->GetPhysicsComponent(), AxisType::Vertical);
	//				}
	//				//else allow current velocity
	//			}
	//			else if ((boundsWorldPosA.min.y > boundsWorldPosB.max.y) && (boundsWorldPosA.min.y < boundsWorldPosB.max.y + collisionPadding)) { // A collides with B from above
	//				//OutputDebugString(L"[Notice] Vertical Collision detected.\n");

	//				//if player is A prevent it from moving further
	//				if (getObjRef[ia].get()->isPlayer && velocityHolderA.y > 0) {
	//					getObjRef[ia].get()->GetPhysicsComponent()->SetVelocity(velocityHolderA.x, 0);
	//				}
	//				else if (!getObjRef[ia].get()->isPlayer) { //Deflect if not player
	//					DeflectObj(getObjRef[ia].get()->GetPhysicsComponent(), AxisType::Vertical);
	//				}
	//				//else allow current velocity

	//				//if player is B prevent it from moving further
	//				if (getObjRef[ib].get()->isPlayer && velocityHolderB.y < 0) {
	//					getObjRef[ib].get()->GetPhysicsComponent()->SetVelocity(velocityHolderA.x, 0);
	//				}
	//				else if (!getObjRef[ib].get()->isPlayer) { //Deflect if not player
	//					DeflectObj(getObjRef[ib].get()->GetPhysicsComponent(), AxisType::Vertical);
	//				}
	//				//else allow current velocity
	//			}

	//		}
	//	}
	//	startingIndexA++;
	//	startingIndexB = startingIndexA + 1;
	//}

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
void PhysicsSystem::DeflectObj(PhysicsComponent* physComponentRef, AxisType collisionType) {
	//Note: deflecting an object with(0, 0) velocity will not apply changes because anything multiplied by 0 is 0.

	if (collisionType == Diagonal) { //Diagonal
		physComponentRef->SetVelocity(physComponentRef->GetVelocity().x * -1, physComponentRef->GetVelocity().y * -1);
	}
	else if (collisionType == Vertical) { //Vertical
		physComponentRef->SetVelocity(physComponentRef->GetVelocity().x, physComponentRef->GetVelocity().y * -1);
	}
	else if (collisionType == Horizontal) { //Horizontal
		physComponentRef->SetVelocity(physComponentRef->GetVelocity().x * -1, physComponentRef->GetVelocity().y);
	}
}

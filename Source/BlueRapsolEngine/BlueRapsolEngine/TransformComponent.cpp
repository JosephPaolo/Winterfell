#include "../../BlueRapsolEngine/BlueRapsolEngine/TransformComponent.h"

using namespace BRComponentType;

TransformComponent::TransformComponent() {
	type = Transform;

	position.x = 0;
	position.y = 0;

	eulerAngle = 0;

	scalar.x = 1;
	scalar.y = 1;
}

//TransformComponent::TransformComponent(GameObject &getObjRef) {
//	type = Transform;
//
//	objRef = &getObjRef;
//
//	position.x = 0;
//	position.y = 0;
//
//	eulerAngle = 0;
//
//	scalar.x = 1;
//	scalar.y = 1;
//}

TransformComponent::~TransformComponent(void) {
	for (unsigned int i = 0; i < children.size(); i++) {
		delete children[i];
	}
}

void TransformComponent::SetTransform(const sf::Transform &matrix) {
	localTransform = matrix;

	if (!parent) {
		worldTransform = matrix;
	}

	Update();
}

//TODO revise to get true transfrom
sf::Transform TransformComponent::GetLocalTransform() {
	return localTransform;
}

//TODO revise to get true transfrom
sf::Transform TransformComponent::GetWorldTransform() {
	return worldTransform;
}

void TransformComponent::AddChild(TransformComponent* getChildRef) {
	children.push_back(getChildRef);
	getChildRef->parent = this;
}

void TransformComponent::SetParent(TransformComponent& getParentRef) {
	parent = &getParentRef;
}

void TransformComponent::SetPosition(sf::Vector2f setPosition) {
	position.x = setPosition.x; position.y = setPosition.y;

	//localTransform = sf::Transform::Identity;
	//localTransform.translate(setPosition.x, setPosition.y);

	/*try {
		objRef->GetRenderComponent()->UpdateRenderObjPos(setPosition.x, setPosition.y);
	}
	catch (...) {
		OutputDebugString(L"Exception Happened.\n");
	}*/

	Update();
}

void TransformComponent::SetPosition(float setX, float setY) {
	position.x = setX; position.y = setY;

	//localTransform = sf::Transform::Identity;
	//localTransform.translate(setX, setY);

	/*try {
		objRef->GetRenderComponent()->UpdateRenderObjPos(setX, setY);
	}
	catch (...) {
		OutputDebugString(L"Exception Happened.\n");
	}*/

	Update();
}

BRDataType::Vector2 TransformComponent::GetPosition() {
	return position;
}

void TransformComponent::Update(float msec) {
	if (parent) { //This node has a parent...
		worldTransform = parent->worldTransform * localTransform;
	}
	else { //Root node, world transform is local transform!
		worldTransform = localTransform;
	}
	for (std::vector<TransformComponent*>::iterator i = children.begin(); i != children.end(); ++i) {
		(*i)->Update(msec);
	}
}

void TransformComponent::Update() {
	if (parent) { //This node has a parent...
		worldTransform = parent->worldTransform * localTransform;
	}
	else { //Root node, world transform is local transform!
		worldTransform = localTransform;
	}
	for (std::vector<TransformComponent*>::iterator i = children.begin(); i != children.end(); ++i) {
		(*i)->Update();
	}
}
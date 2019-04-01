#include "../../BlueRapsolEngine/BlueRapsolEngine/TransformComponent.h"

using namespace BlueRapsolEnums;

TransformComponent::TransformComponent() {
	type = Transform;

	position.x = 0;
	position.y = 0;

	eulerAngle = 0;

	scalar.x = 1;
	scalar.y = 1;
}

TransformComponent::TransformComponent(RenderComponent &getRenderRef) {
	type = Transform;

	renderPtr = &getRenderRef;

	position.x = 0;
	position.y = 0;

	eulerAngle = 0;

	scalar.x = 1;
	scalar.y = 1;
}

void TransformComponent::SetRenderRef(RenderComponent &getRenderRef) {
	renderPtr = &getRenderRef;
}

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

void TransformComponent::SetTransform(sf::Transform &matrix) {
	localTransform = matrix;

	if (!parent) {
		worldTransform = matrix;
	}

	Update();
}

sf::Transform TransformComponent::GetLocalTransform() {
	return localTransform;
}

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

	try {
		SetTransform(renderPtr->UpdateRenderObjPos(setPosition.x, setPosition.y));
	}
	catch (...) {
		OutputDebugString(L"Exception Happened.\n");
	}

	Update();
}

//Sets the position of render object, gets the transform, uses it to update transform as well as its children
void TransformComponent::SetPosition(float setX, float setY) {
	position.x = setX; position.y = setY;

	//localTransform = sf::Transform::Identity;
	//localTransform.translate(setX, setY);

	try {
		//Current Issue: Given new xy coordinates, We can only acquire the new transform of an object after applying the xy changes to the render object. 
		//So we can't truly have the transform component separate from the render component if we want to multiply object transform.
		SetTransform(renderPtr->UpdateRenderObjPos(setX, setY)); //UpdateRenderObjPos() returns a transform AND applies the new coordinates to the render object.
	}
	catch (...) {
		OutputDebugString(L"Exception Happened.\n");
	}

	//Update();
}

//Sets the position of render object, gets the transform, uses it to update transform as well as its children
void TransformComponent::SetEulerAngle(float setDegree) {
	eulerAngle = setDegree;

	try {
		SetTransform(renderPtr->UpdateRenderObjEuler(setDegree));
	}
	catch (...) {
		OutputDebugString(L"Exception Happened.\n");
	}

	Update();
}

float TransformComponent::GetEulerAngle() {
	return eulerAngle;
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

	//Update with new x y position
	position = renderPtr->GetRenderObjPos();

	//Update render object
	renderPtr->UpdateRenderObjPos(position.x, position.y);

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

	//Update with new x y position
	//position = renderPtr->GetRenderObjPos();

	//Update render object
	//renderPtr->UpdateRenderObjPos(position.x, position.y);

	for (std::vector<TransformComponent*>::iterator i = children.begin(); i != children.end(); ++i) {
		(*i)->Update();
	}
}
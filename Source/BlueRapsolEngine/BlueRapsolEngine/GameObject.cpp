#include "../../BlueRapsolEngine/BlueRapsolEngine/GameObject.h"

<<<<<<< HEAD
using namespace BRComponentType;
using namespace BRShapeType;

GameObject::GameObject() {
	//Add new Transfrom and Physics component to the object
	TransformComponent* ptrTransformComponent;
	PhysicsComponent* ptrPhysicsComponent;
	TransformComponent newTransformComponent; 
	PhysicsComponent newPhysicsComponent;
	ptrTransformComponent = &newTransformComponent;
	ptrPhysicsComponent = &newPhysicsComponent;
	componentList.push_back(ptrTransformComponent);
	componentList.push_back(ptrPhysicsComponent);

	//sf::Transform defaultValues;
	//sf::Transform defaultValues(10, 10, 10, 10, 10, 10, 10, 10, 10);
	parent = NULL;
	shape = Square;
	color = sf::Color(100, 250, 50);
	position.x = 0; position.y = 0; //TEMP

}

GameObject::~GameObject(void) {
	for (unsigned int i = 0; i < children.size(); i++) {
		delete children[i];
	}
}

void GameObject::SetTransform(const sf::Transform &matrix) {
	localTransform = matrix;

	if (!parent) {
		worldTransform = matrix;
	}

	Update();
}

void GameObject::SetVelocity(Vector2 newVelocity) {
	velocity = newVelocity;
}

void GameObject::SetVelocity(float setX, float setY) {
	velocity.x = setX; velocity.y = setY;
}

void GameObject::SetDrawableIndex(int setIndex) {
	drawableIndex = setIndex;
}

void GameObject::AddChild(GameObject* getChildRef) {
	children.push_back(getChildRef);
	getChildRef->parent = this;
}

void GameObject::SetParent(GameObject& getParentRef) {
	parent = &getParentRef;
}

sf::Transform GameObject::GetLocalTransform() {
	return localTransform;
}

sf::Transform GameObject::GetWorldTransform() {
	return worldTransform;
}

void GameObject::SetShape(ShapeType setShape) {
	shape = setShape;
}

ShapeType GameObject::GetShape() {
	return shape;
}

void GameObject::SetColor(sf::Color setColor) {
	color = setColor;
}

sf::Color GameObject::GetColor() {
	return color;
}

void GameObject::SetPosition(sf::Vector2f setPosition) {
	position = setPosition;

	//localTransform = sf::Transform::Identity;
	localTransform.translate(setPosition.x, setPosition.y);

	Update();
}

void GameObject::SetPosition(float setX, float setY) {
	position.x = setX; position.y = setY;
	
	//localTransform = sf::Transform::Identity;
	localTransform.translate(setX, setY);

	Update();
}

sf::Vector2f GameObject::GetPosition() {
	return position;
}

Vector2 GameObject::GetVelocity() {
	return velocity;
}

//Getcomponent by index
BaseComponent* GameObject::GetComponent(int atIndex) {
	return componentList[atIndex];
}

//Get Component by type
BaseComponent* GameObject::GetComponent(ComponentType ofType) {
	BaseComponent* empty;
	BaseComponent blank;

	for (size_t i = 0; i < componentList.size(); ++i) { 
		if (ofType == ComponentType::None) {

		}
		else if (ofType == ComponentType::Transform && componentList[i]->type == ComponentType::Transform) {
			return componentList[i];
		}
		else if (ofType == ComponentType::Physics && componentList[i]->type == ComponentType::Physics) {
			return componentList[i];
		}
	}

	empty = &blank;
	return empty;
}

PhysicsComponent* GameObject::GetPhysicsComponent() {
	return &physicsComponent;
}

void GameObject::Update(float msec) {
	if (parent) { //This node has a parent...
		worldTransform = parent->worldTransform * localTransform;
	}
	else { //Root node, world transform is local transform!
		worldTransform = localTransform;
	}
	for (std::vector<GameObject*>::iterator i = children.begin(); i != children.end(); ++i) {
		(*i)->Update(msec);
	}
}

void GameObject::Update() {
	if (parent) { //This node has a parent...
		worldTransform = parent->worldTransform * localTransform;
	}
	else { //Root node, world transform is local transform!
		worldTransform = localTransform;
	}
	for (std::vector<GameObject*>::iterator i = children.begin(); i != children.end(); ++i) {
		(*i)->Update();
	}
}
=======
GameObject::GameObject() {
	TransformComponent newTransformComponent;
	//componentList.assign();
}

>>>>>>> d026f1bd18fea1e55892bb25cf994f43d2ab8489

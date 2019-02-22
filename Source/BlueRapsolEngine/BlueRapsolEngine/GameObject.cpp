#include "../../BlueRapsolEngine/BlueRapsolEngine/GameObject.h"

GameObject::GameObject() {
	TransformComponent newTransformComponent; //TODO
	//sf::Transform defaultValues;
	//sf::Transform defaultValues(10, 10, 10, 10, 10, 10, 10, 10, 10);
	parent = NULL;
	shape = Square;
	color = sf::Color(100, 250, 50);
	position.x = 0; position.y = 0; //TEMP
	//defaultValues.translate(10, 10);
	//worldTransform.
	//worldTransform.translate(10, 10);
	//worldTransform.scale(1, 1);
	//localTransform.translate(10, 10);
	//localTransform.scale(1, 1);
	//worldTransform = defaultValues;
	//localTransform = defaultValues;
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
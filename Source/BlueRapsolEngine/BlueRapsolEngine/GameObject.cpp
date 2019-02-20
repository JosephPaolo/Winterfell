#include "../../BlueRapsolEngine/BlueRapsolEngine/GameObject.h"

GameObject::GameObject() {
	TransformComponent newTransformComponent;
	parent = NULL;
}

GameObject::~GameObject(void) {
	for (unsigned int i = 0; i < children.size(); i++) {
		delete children[i];
	}
}

void GameObject::SetTransform(const sf::Transform &matrix) {
	localTransform = matrix;
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

void GameObject::Update(float msec) {
	if (parent) { //This node has a parent...
		worldTransform = parent->worldTransform * localTransform;
	}
	else { //Root node, world transform is local transform!
		worldTransform = localTransform;
	}
	for (vector<GameObject*>::iterator i = children.begin(); i != children.end(); ++i) {
		(*i)->Update(msec);
	}
}
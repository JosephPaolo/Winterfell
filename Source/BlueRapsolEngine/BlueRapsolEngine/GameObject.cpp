#include "../../BlueRapsolEngine/BlueRapsolEngine/GameObject.h"

GameObject::GameObject() {
	TransformComponent newTransformComponent;
	//componentList.assign();
	componentArray[0] = &newTransformComponent; //Temp
}

GameObject::GameObject(InitDirect3DApp* d3dRef, int assignToIndex) {
	TransformComponent newTransformComponent;
	componentArray[0] = &newTransformComponent; //Temp

	renderItemIndex = assignToIndex;
	if (&d3dRef->getRenderItemTransform(assignToIndex)) {
		worldTransform = d3dRef->getRenderItemTransform(assignToIndex);
	}
	localTransform = worldTransform;
	XMStoreFloat4x4(matrix, XMMatrixScaling(1.0f, 1.0f, 1.0f)*XMMatrixTranslation(setPosition.x, setPosition.y, setPosition.z));
}

GameObject::~GameObject(void) {
	for (unsigned int i = 0; i < children.size(); i++) {
		delete children[i];
	}
}

void GameObject::SetTransform(const XMFLOAT4X4 &matrix) {
	localTransform = matrix;
}

void GameObject::AddChild(GameObject* getChildRef) {
	children.push_back(getChildRef);
	getChildRef->parent = this;
}

void GameObject::SetParent(GameObject& getParentRef) {
	parent = &getParentRef;
}

XMFLOAT4X4 GameObject::GetLocalTransform() {
	return localTransform;
}

XMFLOAT4X4 GameObject::GetWorldTransform() {
	return worldTransform;
}

void GameObject::RotateByEuler(float degrees) {

}

void GameObject::Update(float msec) {
	XMMATRIX a; XMMATRIX b; a * b;


	if (parent) { //This node has a parent...
		worldTransform = parent->worldTransform * localTransform;
	}
	else { //Root node, world transform is local transform!
		worldTransform = localTransform;
	}
	for (vector<GameObject*>::iterator i = children.begin(); i !=
		children.end(); ++i) {
		(*i)->Update(msec);
	}
}
#include "../../BlueRapsolEngine/BlueRapsolEngine/BaseComponent.h"
#include "../../BlueRapsolEngine/BlueRapsolEngine/TransformComponent.h"
#include "../../DirectX/Framework/InitDirect3DApp.h"
#include <list>

#pragma once

class GameObject {

public: 
	GameObject::GameObject(); //Makes new render item TODO
	GameObject::GameObject(InitDirect3DApp* d3dRef, int assignToIndex); //Assign to existing render item 
	GameObject::~GameObject();

	XMFLOAT4X4 GetLocalTransform();
	XMFLOAT4X4 GetWorldTransform();
	void SetTransform(const XMFLOAT4X4 &matrix);
	void SetParent(GameObject& passParentRef);
	void AddChild(GameObject* passChildRef);
	void RotateByEuler(float degrees); //Changes children's world as well
	void Update(float msec);
	//void UpdateRenderItems();
	
protected: 
	//std::list<BaseComponent> componentList;
	BaseComponent* componentArray[1]; //temp

	GameObject* parent;
	std::vector<GameObject*> children;
	XMMATRIX matrix;
	XMFLOAT4X4 worldTransform;
	XMFLOAT4X4 localTransform;
	int renderItemIndex;
};

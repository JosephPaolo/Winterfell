#include "../../BlueRapsolEngine/BlueRapsolEngine/BaseComponent.h"
#include "../../BlueRapsolEngine/BlueRapsolEngine/TransformComponent.h"
#include <list>
#include <SFML/Graphics.hpp>

#pragma once

class GameObject {

public: 
	GameObject::GameObject(); //Makes new render item TODO
	//GameObject::GameObject(InitDirect3DApp* d3dRef, int assignToIndex); //Assign to existing render item 
	GameObject::~GameObject(void);

	sf::Transform GetLocalTransform();
	sf::Transform GetWorldTransform();
	void SetTransform(const sf::Transform &matrix);
	void SetParent(GameObject& passParentRef);
	void AddChild(GameObject* passChildRef);
	//void RotateByEuler(float degrees); //Changes children's world as well
	void Update(float msec);
	//void UpdateRenderItems();
	
protected: 
	//std::list<BaseComponent> componentList;
	//BaseComponent* componentArray[1]; //temp

	GameObject* parent;
	std::vector<GameObject*> children;
	sf::Transform worldTransform;
	sf::Transform localTransform;
};

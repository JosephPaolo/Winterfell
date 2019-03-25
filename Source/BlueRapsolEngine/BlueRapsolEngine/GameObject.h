#include "../../BlueRapsolEngine/BlueRapsolEngine/BaseComponent.h"
#include "../../BlueRapsolEngine/BlueRapsolEngine/TransformComponent.h"
#include "BRDataTypes.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include <list>
#include <SFML/Graphics.hpp>

#pragma once

using namespace BRDataType;
using namespace BRComponentType;
using namespace BRShapeType;

class GameObject {

public: 
	GameObject::GameObject(); //Makes new render item TODO
	GameObject::GameObject(float getX, float getY);
	GameObject::GameObject(float getX, float getY, float width, float height);
	GameObject::GameObject(sf::Texture, float getX, float getY);
	GameObject::GameObject(sf::Texture, float getX, float getY, float width, float height);
	GameObject::~GameObject(void);
	
	ShapeType GetShape();
	sf::Color GetColor();
	
	void SetShape(ShapeType setShape);
	void SetColor(sf::Color setColor);

	PhysicsComponent* GetPhysicsComponent();
	RenderComponent* GetRenderComponent();
	TransformComponent* GetTransformComponent();

	template<class T>
	T GetComponent(T componentType);

protected: 
	//std::vector<BaseComponent*> componentList; //TODO broken rn
	std::vector<BaseComponent*> componentList;

	TransformComponent transformComponent; //Temp
	PhysicsComponent physicsComponent; //Temp
	RenderComponent renderComponent; //Temp

	ShapeType shape;
	sf::Color color;
};

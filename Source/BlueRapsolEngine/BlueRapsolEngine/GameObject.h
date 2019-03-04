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
	GameObject::~GameObject(void);

	ShapeType GetShape();
	sf::Color GetColor();
	
	void SetShape(ShapeType setShape);
	void SetColor(sf::Color setColor);

	PhysicsComponent* GetPhysicsComponent();
	RenderComponent* GetRenderComponent();
	TransformComponent* GetTransformComponent();

protected: 
	//std::vector<BaseComponent*> componentList; //TODO broken rn
	TransformComponent transformComponent; //Temp
	PhysicsComponent physicsComponent; //Temp
	RenderComponent renderComponent; //Temp

	ShapeType shape;
	sf::Color color;
};

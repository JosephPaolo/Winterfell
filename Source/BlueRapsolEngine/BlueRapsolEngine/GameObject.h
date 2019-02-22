<<<<<<< HEAD
#include "../../BlueRapsolEngine/BlueRapsolEngine/BaseComponent.h"
#include "../../BlueRapsolEngine/BlueRapsolEngine/TransformComponent.h"
#include "BRDataTypes.h"
#include "PhysicsComponent.h"
#include <list>
#include <SFML/Graphics.hpp>

#pragma once

using namespace BRDataType;
using namespace BRComponentType;
using namespace BRShapeType;

class GameObject {

public: 
	GameObject::GameObject(); //Makes new render item TODO
	//GameObject::GameObject(InitDirect3DApp* d3dRef, int assignToIndex); //Assign to existing render item 
	GameObject::~GameObject(void);

	sf::Transform GetLocalTransform();
	sf::Transform GetWorldTransform();
	ShapeType GetShape();
	sf::Color GetColor();
	sf::Vector2f GetPosition(); //TEMP
	Vector2 GetVelocity();

	void SetTransform(const sf::Transform &matrix);
	void SetTransform(sf::Transform &matrix);
	void SetParent(GameObject& passParentRef);
	void AddChild(GameObject* passChildRef);
	void SetShape(ShapeType setShape);
	void SetColor(sf::Color setColor);
	void SetPosition(sf::Vector2f setPosition);
	void SetPosition(float setX, float setY);
	void SetDrawableIndex(int setIndex);
	void SetVelocity(float setX, float setY);
	void SetVelocity(Vector2 newVelocity);

	BaseComponent* GetComponent(int atIndex);
	BaseComponent* GetComponent(ComponentType ofType); //Doesn't work rn
	PhysicsComponent* GetPhysicsComponent();
	//void AddComponent();

	void Update();
	void Update(float msec); //TODO: figure out why we need msec parameter

protected: 
	std::vector<BaseComponent*> componentList; //TODO broken rn
	TransformComponent transformComponent; //Temp
	PhysicsComponent physicsComponent; //Temp
	GameObject* parent;
	std::vector<GameObject*> children;
	sf::Transform worldTransform;
	sf::Transform localTransform;
	ShapeType shape;
	sf::Color color;
	int drawableIndex; //index to the sf::drawable array. It is a list of all things that should be rendered.
	sf::Vector2f position; //TEMP
	Vector2 velocity; //Velocity moves the object per tick
=======

#include "../../BlueRapsolEngine/BlueRapsolEngine/BaseComponent.h"
#include "../../BlueRapsolEngine/BlueRapsolEngine/TransformComponent.h"
#include <list>

#pragma once

class GameObject {

public:
	GameObject::GameObject();

protected:
	std::list<BaseComponent> componentList;

>>>>>>> d026f1bd18fea1e55892bb25cf994f43d2ab8489
};

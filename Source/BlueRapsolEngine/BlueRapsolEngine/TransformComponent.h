#pragma once

#include "../../BlueRapsolEngine/BlueRapsolEngine/BaseComponent.h"
#include "../../BlueRapsolEngine/BlueRapsolEngine/BRDataTypes.h"
#include <SFML/Graphics.hpp>
#include "windows.h"

class TransformComponent : public BaseComponent{

public:
	TransformComponent();
	//TransformComponent(GameObject &getObjRef);
	~TransformComponent(void);

	//GameObject* objRef;
	TransformComponent* parent;
	std::vector<TransformComponent*> children;
	sf::Transform worldTransform;
	sf::Transform localTransform;

	BRDataType::Vector2 position;
	BRDataType::Vector2 scalar;
	float eulerAngle;

	void Update();
	void Update(float msec); //TODO: figure out why we need msec parameter

	sf::Transform GetLocalTransform();
	sf::Transform GetWorldTransform();
	void SetTransform(const sf::Transform &matrix);
	void SetTransform(sf::Transform &matrix);
	void SetParent(TransformComponent& passParentRef);
	void AddChild(TransformComponent* passChildRef);
	void SetPosition(sf::Vector2f setPosition);
	void SetPosition(float setX, float setY);

	BRDataType::Vector2 GetPosition();
};

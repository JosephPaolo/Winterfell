#pragma once

#include "../../BlueRapsolEngine/BlueRapsolEngine/BaseComponent.h"
#include "../../BlueRapsolEngine/BlueRapsolEngine/BRDataTypes.h"
#include <SFML/Graphics.hpp>
#include "windows.h"
#include "RenderComponent.h"

class TransformComponent : public BaseComponent{

public:
	TransformComponent();
	TransformComponent(RenderComponent &getRenderRef);
	~TransformComponent(void);

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
	void SetRenderRef(RenderComponent &getRenderRef);
	void SetEulerAngle(float setDegree);
	float GetEulerAngle();

	BRDataType::Vector2 GetPosition();

private:
	//GameObject* objRef;
	RenderComponent* renderPtr;
	TransformComponent* parent;
	std::vector<TransformComponent*> children;
	sf::Transform worldTransform;
	sf::Transform localTransform;

	BRDataType::Vector2 position;
	BRDataType::Vector2 scalar;
	float eulerAngle;
};

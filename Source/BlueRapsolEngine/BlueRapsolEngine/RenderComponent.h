#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "BaseComponent.h"
#include "BRDataTypes.h"

class RenderComponent : BaseComponent {

public:
	//void setRenderObjIndex(int newRenderObjIndex);
	//int getRenderObjIndex();

	RenderComponent();

	std::unique_ptr<sf::RectangleShape> renderObjPtr;

	//void UpdateRenderObj(const std::unique_ptr<sf::RectangleShape>& getRenderObjRef);
	sf::Transform UpdateRenderObjPos(float getPosX, float getPosY);
	void UpdateRenderObjTransform(const std::unique_ptr<sf::RectangleShape>& getRenderObjRef);
	sf::Transform UpdateRenderObjEuler(float getAngle);
	BRDataType::Vector2 GetRenderObjPos();


private:
	
};

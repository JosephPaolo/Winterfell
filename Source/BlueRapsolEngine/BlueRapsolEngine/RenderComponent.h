#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "BaseComponent.h"
#include "BRDataTypes.h"

class RenderComponent : public BaseComponent {

public:
	//void setRenderObjIndex(int newRenderObjIndex);
	//int getRenderObjIndex();

	RenderComponent();
	//RenderComponent(sf::Texture);

	//std::unique_ptr<sf::RectangleShape> renderObjPtr;
	std::unique_ptr<sf::Sprite> renderObjPtr;
	//std::unique_ptr<sf::Sprite> renderSpritePtr;

	//void UpdateRenderObj(const std::unique_ptr<sf::RectangleShape>& getRenderObjRef);
	sf::Transform UpdateRenderObjPos(float getPosX, float getPosY);
	void UpdateRenderObjTransform(const std::unique_ptr<sf::RectangleShape>& getRenderObjRef);
	sf::Transform UpdateRenderObjEuler(float getAngle);
	BRDataType::Vector2 GetRenderObjPos();
	void SetTexture(sf::Texture newTexture);

private:
	
};

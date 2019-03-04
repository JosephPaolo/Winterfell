
#include "RenderComponent.h"

RenderComponent::RenderComponent() {
	renderObjPtr = std::make_unique<sf::RectangleShape>(sf::Vector2f(50, 50));
}

void RenderComponent::UpdateRenderObjPos(float getPosX, float getPosY) {
	renderObjPtr.get()->setPosition(getPosX, getPosY);
}
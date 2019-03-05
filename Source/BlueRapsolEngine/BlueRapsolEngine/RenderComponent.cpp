
#include "RenderComponent.h"

RenderComponent::RenderComponent() {
	renderObjPtr = std::make_unique<sf::RectangleShape>(sf::Vector2f(50, 50));
}

sf::Transform RenderComponent::UpdateRenderObjPos(float getPosX, float getPosY) {
	renderObjPtr.get()->setPosition(getPosX, getPosY);

	return renderObjPtr.get()->getTransform();
}

void RenderComponent::UpdateRenderObjTransform(const std::unique_ptr<sf::RectangleShape>& getRenderObjRef) {

}

sf::Transform RenderComponent::UpdateRenderObjEuler(float getAngle) {
	renderObjPtr.get()->setRotation(getAngle);

	return renderObjPtr.get()->getTransform();
}
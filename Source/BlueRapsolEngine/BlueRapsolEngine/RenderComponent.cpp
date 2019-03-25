
#include "RenderComponent.h"

RenderComponent::RenderComponent() {
	//renderObjPtr = std::make_unique<sf::RectangleShape>(sf::Vector2f(50, 50));
	renderObjPtr = std::make_unique<sf::Sprite>();
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

BRDataType::Vector2 RenderComponent::GetRenderObjPos() {
	BRDataType::Vector2 getVector(renderObjPtr.get()->getPosition().x, renderObjPtr.get()->getPosition().y);

	return getVector;
}

void RenderComponent::SetTexture(sf::Texture newTexture) {
	renderObjPtr->setTexture(newTexture, false);
}
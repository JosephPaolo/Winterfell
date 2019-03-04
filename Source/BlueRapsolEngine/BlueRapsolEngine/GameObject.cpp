#include "../../BlueRapsolEngine/BlueRapsolEngine/GameObject.h"

using namespace BRComponentType;
using namespace BRShapeType;

GameObject::GameObject() {
	transformComponent.SetRenderRef(renderComponent);
	transformComponent.SetTransform(renderComponent.renderObjPtr.get()->getTransform()); //Set SFML shape transform to transform component
}

GameObject::~GameObject(void) {

}

void GameObject::SetShape(ShapeType setShape) {
	shape = setShape;
}

ShapeType GameObject::GetShape() {
	return shape;
}

void GameObject::SetColor(sf::Color setColor) {
	color = setColor;
}

sf::Color GameObject::GetColor() {
	return color;
}

PhysicsComponent* GameObject::GetPhysicsComponent() {
	return &physicsComponent;
}

RenderComponent* GameObject::GetRenderComponent() {
	return &renderComponent;
}

TransformComponent* GameObject::GetTransformComponent() {
	return &transformComponent;
}
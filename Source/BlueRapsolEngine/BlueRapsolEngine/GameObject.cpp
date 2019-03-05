#include "../../BlueRapsolEngine/BlueRapsolEngine/GameObject.h"

using namespace BRComponentType;
using namespace BRShapeType;

GameObject::GameObject() {
	transformComponent.SetRenderRef(renderComponent);
	transformComponent.SetTransform(renderComponent.renderObjPtr.get()->getTransform()); //Set SFML shape transform to transform component
	physicsComponent.SetBounds(Vector2(0, 0), Vector2(50, 50));
}

GameObject::GameObject(float xPos, float yPos) {
	transformComponent.SetRenderRef(renderComponent);
	//transformComponent.SetTransform(renderComponent.renderObjPtr.get()->getTransform()); //Set SFML shape transform to transform component
	physicsComponent.SetBounds(Vector2(0, 0), Vector2(50, 50));
	transformComponent.SetPosition(xPos, yPos);
	transformComponent.SetTransform(renderComponent.renderObjPtr.get()->getTransform());
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
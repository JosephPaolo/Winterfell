#include "../../BlueRapsolEngine/BlueRapsolEngine/GameObject.h"

using namespace BlueRapsolEnums;

GameObject::GameObject() {

	TransformComponent newTransform;
	PhysicsComponent newPhysics; 
	RenderComponent newRender; 

	transformComponent.SetRenderRef(renderComponent);
	transformComponent.SetTransform(renderComponent.renderObjPtr.get()->getTransform()); //Set SFML shape transform to transform component
	physicsComponent.SetBounds(Vector2(0, 50), Vector2(50, 0));

	componentList.push_back(&newTransform);
	componentList.push_back(&physicsComponent);
	componentList.push_back(&renderComponent);
}

GameObject::GameObject(float xPos, float yPos) {
	transformComponent.SetRenderRef(renderComponent);
	physicsComponent.SetBounds(Vector2(0, 50), Vector2(50, 0));
	transformComponent.SetPosition(xPos, yPos);
	transformComponent.SetTransform(renderComponent.renderObjPtr.get()->getTransform());
}

GameObject::GameObject(float xPos, float yPos, float width, float height) {
	transformComponent.SetRenderRef(renderComponent);
	//renderComponent.renderObjPtr.get()->setSize(sf::Vector2f(width, height));
	physicsComponent.SetBounds(Vector2(0, height), Vector2(width, 0));
	transformComponent.SetPosition(xPos, yPos);
	transformComponent.SetTransform(renderComponent.renderObjPtr.get()->getTransform());
}

GameObject::GameObject(sf::Texture setSpriteTexture, float xPos, float yPos) {
	transformComponent.SetRenderRef(renderComponent);
	//renderComponent.renderObjPtr.get()->setSize(sf::Vector2f(width, height));
	renderComponent.SetTexture(setSpriteTexture);
	physicsComponent.SetBounds(Vector2(0, 50), Vector2(50, 0));
	transformComponent.SetPosition(xPos, yPos);
	transformComponent.SetTransform(renderComponent.renderObjPtr.get()->getTransform());
}

GameObject::GameObject(sf::Texture setSpriteTexture, float xPos, float yPos, float width, float height) {
	transformComponent.SetRenderRef(renderComponent);
	//renderComponent.renderObjPtr.get()->setSize(sf::Vector2f(width, height));
	//renderComponent.renderObjPtr.get()->setScale(sf::Vector2f(width, height));
	renderComponent.SetTexture(setSpriteTexture);
	physicsComponent.SetBounds(Vector2(0, height), Vector2(width, 0));
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

template<class T>
T GameObject::GetComponent(ComponentType compType) {
	TransformComponent* transformHolder;
	PhysicsComponent* physicsHolder;
	RenderComponent* renderHolder;

	switch (compType) {
	case TransformComponent:
		for each (BaseComponent component in componentList) {
			if (compType == ComponentType::Transform) {
				transformHolder = component;
				return transformHolder;
			}
		}

	case PhysicsComponent:
		for each (BaseComponent component in componentList) {
			if (compType == ComponentType::Physics) {
				physicsHolder = component;
				return physicsHolder;
			}
		}

	case RenderComponent:
		for each (BaseComponent component in componentList) {
			if (compType == ComponentType::Renderer) {
				renderHolder = component;
				return renderHolder;
			}
		}
	}

}
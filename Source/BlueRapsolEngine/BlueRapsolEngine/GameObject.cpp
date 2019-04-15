#include "../../BlueRapsolEngine/BlueRapsolEngine/GameObject.h"

using namespace BlueRapsolEnums;

GameObject::GameObject() {

	transformComponent.SetRenderRef(renderComponent);
	transformComponent.SetTransform(renderComponent.renderObjPtr.get()->getTransform()); //Set SFML shape transform to transform component
	physicsComponent.SetBounds(Vector2(0, 50), Vector2(50, 0));
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
	PhysicsComponent * physicsHolder;

	//Check if component already exists
	/*for (int i = 0; i < componentList.size(); i++) {
		if (componentList[i]->type == ComponentType::Physics) {
			physicsHolder = (PhysicsComponent*)componentList[i];
			return physicsHolder;
		}
	}*/

	return &physicsComponent;
}

RenderComponent* GameObject::GetRenderComponent() {
	RenderComponent* renderHolder;

	//Check if component already exists
	/*for (int i = 0; i < componentList.size(); i++) {
		if (componentList[i]->type == ComponentType::Renderer) {
			renderHolder = (RenderComponent*)componentList[i];
			return renderHolder;
		}
	}*/

	return &renderComponent;
}

TransformComponent* GameObject::GetTransformComponent() {
	TransformComponent* transformHolder;

	//Check if component already exists
	/*for (int i = 0; i < componentList.size(); i++) {
		if (componentList[i]->type == ComponentType::Transform) {
			transformHolder = (TransformComponent*)componentList[i];
			return transformHolder;
		}
	}*/

	return &transformComponent;
}

void GameObject::AddComponent(ComponentType componentType) {

	//TODO downcast instead of making all posiibilites
	TransformComponent transformHolder;
	PhysicsComponent physicsHolder;
	RenderComponent renderHolder;

	//Check if component already exists
	for (int i = 0; i < componentList.size(); i++) {
		if (componentList[i]->type == componentType) {
			return;
		}
	}

	//Add new component
	switch (componentType) {
	case ComponentType::Transform:
		transformHolder.type = ComponentType::Transform;
		componentList.push_back(&transformHolder);
		break;
	case ComponentType::Physics:
		physicsHolder.type = ComponentType::Physics;
		componentList.push_back(&physicsHolder);
		break;
	case ComponentType::Renderer:
		renderHolder.type = ComponentType::Renderer;
		componentList.push_back(&renderHolder);
		break;
	default:
		//Handle component not found
		break;
	}

}

template<class T>
T* GameObject::GetComponent(ComponentType componentType) {
	TransformComponent* transformHolder;
	PhysicsComponent* physicsHolder;
	RenderComponent* renderHolder;

	switch (componentType) {
	case ComponentType::Transform:
		for (int i = 0; i < componentList.size(); i++) {
			if (componentList[i]->type == componentType) {
				transformHolder = (TransformComponent*)componentList[i];
				return transformHolder;
			}
		}
		break;
	case ComponentType::Physics:
		for (int i = 0; i < componentList.size(); i++) {
			if (componentList[i]->type == componentType) {
				physicsHolder = (PhysicsComponent*)componentList[i];
				return physicsHolder;
			}
		}
		break;
	case ComponentType::Renderer:
		for (int i = 0; i < componentList.size(); i++) {
			if (componentList[i]->type == componentType) {
				renderHolder = (RenderComponent*)componentList[i];
				return renderHolder;
			}
		}
		break;
	default:
		//Handle component not found
		break;
	}
	


}
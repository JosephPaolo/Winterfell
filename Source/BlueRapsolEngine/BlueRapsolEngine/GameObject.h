
#include "../../BlueRapsolEngine/BlueRapsolEngine/BaseComponent.h"
#include "../../BlueRapsolEngine/BlueRapsolEngine/TransformComponent.h"
#include <list>

#pragma once

class GameObject {

public:
	GameObject::GameObject();

protected:
	std::list<BaseComponent> componentList;

};

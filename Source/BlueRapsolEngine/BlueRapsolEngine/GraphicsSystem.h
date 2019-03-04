#pragma once
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "GameObject.h"

class GraphicsSystem {
public:

	void UpdateGraphics();
	//void UpdateGraphics(sf::RenderWindow & renderWindow, const std::vector<std::unique_ptr<sf::RectangleShape>>& getRenderObjRef);

	void DrawRenderObjects(sf::RenderWindow & renderWindow, const std::vector<std::unique_ptr<GameObject>>& getRenderObjRef);
};

#pragma once
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "GameObject.h"

class GraphicsSystem {
public:
	
	std::map<std::string, sf::Texture> textureMap; //texture map

	void UpdateGraphics();
	//void UpdateGraphics(sf::RenderWindow & renderWindow, const std::vector<std::unique_ptr<sf::RectangleShape>>& getRenderObjRef);

	void DrawRenderObjects(sf::RenderWindow & renderWindow, const std::vector<std::unique_ptr<GameObject>>& getRenderObjRef);

	bool LoadTextureFromFile(std::string key, std::string filePath);
	sf::Texture GetTextureByKey(std::string key);

private: 
	
};

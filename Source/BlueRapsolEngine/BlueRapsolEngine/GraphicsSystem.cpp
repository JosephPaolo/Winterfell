#include "GraphicsSystem.h"

void GraphicsSystem::UpdateGraphics() {

}

void GraphicsSystem::DrawRenderObjects(sf::RenderWindow & renderWindow, const std::vector<std::unique_ptr<GameObject>>& getAllObjRef) {
	std::wstring msg; //Used for formatting debug messages

	renderWindow.clear(sf::Color::Black); //Clear the window with black color

	//sf::Texture * texturePtr;
	//sf::Texture newTexture;
	/*sf::Sprite newSprite;*/
	//texturePtr = &newTexture;
	//if (!newTexture.loadFromFile("../../../Assets/50x50.png")) {
	//	// error...
	//}
	/*newSprite.setTexture(textureMap["myTextureName"]);
	renderWindow.draw(newSprite);*/

	//if (textureMap["myTextureName"]) {
	//	OutputDebugString(L"Yes.\n");
	//}

	//msg = L"\ntextureMap.size(): " + std::to_wstring(textureMap.size());
	//OutputDebugString(msg.c_str());

	for (int i = 0; i < getAllObjRef.size(); i++) { //Draw all render items
		try {
			renderWindow.draw(*getAllObjRef[i].get()->GetRenderComponent()->renderObjPtr, getAllObjRef[i].get()->GetTransformComponent()->GetWorldTransform());
		}
		catch (...) {
			OutputDebugString(L"Exception Happened.\n");
		}

		//Update transform component position with render object position
		getAllObjRef[i].get()->GetTransformComponent()->SetPosition(getAllObjRef[i].get()->GetRenderComponent()->renderObjPtr.get()->getPosition());

	}

	renderWindow.display(); //End the current frame
}

bool GraphicsSystem::LoadTextureFromFile(std::string key, std::string filePath) {
	sf::Texture newTexture;

	try {
		if (!newTexture.loadFromFile(filePath)){
			OutputDebugString(L"[Error] Loading texture failed!\n");
			return false;
		}

		textureMap.insert(std::make_pair(key, newTexture)); //save reference to map
	}
	catch (...) {
		OutputDebugString(L"Exception Happened.\n");
	}

	return true;
}

sf::Texture GraphicsSystem::GetTextureByKey(std::string key) {
	return textureMap[key];
}
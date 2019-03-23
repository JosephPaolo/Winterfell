#include "GraphicsSystem.h"

void GraphicsSystem::UpdateGraphics() {

}

void GraphicsSystem::DrawRenderObjects(sf::RenderWindow & renderWindow, const std::vector<std::unique_ptr<GameObject>>& getAllObjRef) {
	std::wstring msg; //Used for formatting debug messages

	renderWindow.clear(sf::Color::Black); //Clear the window with black color

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
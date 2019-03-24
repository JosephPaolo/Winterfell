
#include "BlueRapsolApp.h"

BlueRapsolApp::BlueRapsolApp(HINSTANCE hInstance) : BlueRapsolEngine::BlueRapsolEngine(hInstance){

}

bool BlueRapsolApp::Initialize() {
	//Insure it is the only instance
	if (!IsOnlyInstance(MUTEX_APP_NAME)) {
		return false;
	}

	return true;
}

void BlueRapsolApp::GameStart() {
	std::wstring msg; //Used for formatting debug messages

	//Load Sound
	audioSys.LoadBuffer();

	//Play Sound
	//audioSys.SoundPlay();

	//Example
	//Instantiate() creates a new GameObject and stores it in an array. Instantiate() returns the index position so you can reference the object later on.
	//Note: It uses a unique pointer so you cannot have multiple references of the same object. So you access the object through allObjects[ObjIndex].get().
	int ObjIndex = Instantiate(300, 200); //Creates a new GameObject and since it is the first one its index will be '0'
	allObjects[ObjIndex].get()->GetPhysicsComponent()->SetVelocity(0.05f, 0.07f); //The GameObject will visually move diagonally. Use GetPhysicsComponent() to access Physics component properties.

	//Making the walls
	//Use Instantiate(x position, y position, width, height);
	//Note: The origin of a shape is at the top left.
	//Note: The origin of the world is at the top left. Positive x is rightward and positive y is downward.
	//Note: Collision only works with velocity; you can't change position in BlueRapsolEngine::GameUpdate() and expect it to collide.
	Instantiate(150, 50, 700, 50); //Creates a second new GameObject and since it is the second one its index will be '1'
	Instantiate(150, 275, 700, 50); //its index will be '2'
	Instantiate(125, 50, 50, 500); //its index will be '3'
	Instantiate(500, 50, 50, 500); //its index will be '4'

	//Debugging Example
	//msg = L"Value of ObjIndex: " + std::to_wstring(ObjIndex) + L"\n";
	//OutputDebugString(msg.c_str());
}

void BlueRapsolApp::GameUpdate() {
	//Example
	//This moves our second created object (index 1) towards the right by 0.2f every tick
	//float newPositionX = allObjects[1].get()->GetTransformComponent()->GetPosition().x + 0.05f; //The original x position + 0.2f
	//float newPositionY = allObjects[1].get()->GetTransformComponent()->GetPosition().y; //The original y position doesnt change
	//allObjects[1].get()->GetTransformComponent()->SetPosition(newPositionX, newPositionY); //We pass the values to the object with SetPosition()

}

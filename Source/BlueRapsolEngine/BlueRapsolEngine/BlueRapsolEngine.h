//*************************************************************************** 
// File name: BlueRapsolEngine.h
// Authors: Joseph Malibiran, Tsuzuri Okada, Terence Stewart (C) 2018 All Rights Reserved. 
// Created: Sept. 19, 2018
// Last Updated: Feb. 21, 2019
// Version: 0.1.0A
// Description: 
//   This Class will represent the Game Application layer of the Blue Rapsol Engine
// *****************************************************************************

#pragma once

#include <windows.h>
#include <WinBase.h>
#include <memory>
#include "../../BlueRapsolEngine/BlueRapsolEngine/KeyboardListener.h"
#include "../../BlueRapsolEngine/BlueRapsolEngine/MouseListener.h"
#include "../../BlueRapsolEngine/BlueRapsolEngine/GameTimer.h"
#include "SplashScreen.h"
#include "GameObject.h"
#include "BRDataTypes.h"
#include "BREnums.h"
#include <SFML/Graphics.hpp>

class BlueRapsolEngine {

public:
	BlueRapsolEngine(HINSTANCE hInstance);
	//~BlueRapsolEngine();

	KeyboardListener kbInput;
	MouseListener mbInput;

	void Run(HINSTANCE hInstance);

	//Check for sufficient storage space
	bool ChkStorage(unsigned long long requiredBytes, LPCWSTR directory);

	//Check for available RAM and virtual memory
	void ChkMem();

	//Display CPU speed and architecture
	void DisplayCPUArch();
	void DisplayCPUSpeed();

	virtual void GameStart();
	virtual void GameUpdate();

	int Instantiate(); //Creates a square shape at origin
	void SetOBjPosition(int getObjIndex, float setX, float setY);
	//GameObject* Instantiate(ShapeType setShape, BRDataType::Vector3 setPosition);
	//void SetPosition(GameObject & targetObject, BRDataType::Vector3 newPosition);
	//void SetScale(GameObject & targetObject, BRDataType::Vector3 newScalar);
	//void SetEulerAngle(GameObject & targetObject, BRDataType::Vector3 newEulerAngle);
	//void SetTransform(GameObject & targetObject, sf::Transform newTransform);

private:
	std::vector<std::unique_ptr<GameObject>> allObjects; // List of all the objects.
	std::vector<sf::RectangleShape*> allRenderObjects; // List of all the renderable items

	GameTimer mTimer;
	bool isInitializing = true;

	bool IsOnlyInstance(LPCTSTR appName);
	void Initialize(sf::RenderWindow & renderWindow);
	void GameLoop(sf::RenderWindow & renderWindow);
	void DrawRenderObjects(sf::RenderWindow & renderWindow, const std::vector<sf::RectangleShape*>& ritems);
};

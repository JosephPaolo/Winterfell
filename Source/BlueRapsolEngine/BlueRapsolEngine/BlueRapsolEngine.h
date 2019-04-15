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
#include "AudioSystem.h"
#include "GraphicsSystem.h"
#include "PhysicsSystem.h"
#include "InputSystem.h"
#include <SFML/Graphics.hpp>
#include <chrono>

class BlueRapsolEngine {

public: 
	void Run(HINSTANCE hInstance);

protected:
	BlueRapsolEngine(HINSTANCE hInstance);
	//~BlueRapsolEngine();

	KeyboardListener kbInput;
	MouseListener mbInput;

	//Check if it's the onyl instance
	bool IsOnlyInstance(LPCTSTR appName);

	//Check for sufficient storage space
	bool ChkStorage(unsigned long long requiredBytes, LPCWSTR directory);

	//Check for available RAM and virtual memory
	void ChkMem();

	//Display CPU speed and architecture
	void DisplayCPUArch();
	void DisplayCPUSpeed();

	int Instantiate(); //Creates a square shape at origin
	int Instantiate(std::string setKey);
	int Instantiate(std::string setKey, float getX, float getY);
	int Instantiate(std::string setKey, BRDataType::Vector2 setPos);
	int Instantiate(std::string setKey, float getX, float getY, float width, float height);
	int Instantiate(std::string setKey, std::string setSprite, float getX, float getY);
	int Instantiate(std::string setKey, std::string setSprite, float getX, float getY, float width, float height);

	void SetTexture(std::string objKey, std::string setSprite);

	virtual void GameStart();
	virtual void GameUpdate();
	virtual bool Initialize();

	AudioSystem audioSys;
	GraphicsSystem graphicsSys;
	PhysicsSystem physicsSys;
	InputSystem inputSys;
	float deltaTime;

	std::vector<std::unique_ptr<GameObject>> allObjects; // List of all the objects.
	//std::vector<GameObject*> allObjects; // List of all the objects.
	std::map<std::string, int> getObjIndex; //Get the index value from name

private:
	GameTimer mTimer;
	int loopsPerTick = 128;
	int loopCounter = 0;
	sf::Time time;
	sf::Clock clock;

	bool isInitializing = true;
	bool isPaused = false;

	void Initialize(sf::RenderWindow & renderWindow);
	void GameLoop(sf::RenderWindow & renderWindow);
	//void DrawRenderObjects(sf::RenderWindow & renderWindow);
};

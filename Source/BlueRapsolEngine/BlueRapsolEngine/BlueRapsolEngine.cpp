//*************************************************************************** 
// File name: InitBlueRapsol.h
// Authors: Joseph Malibiran, Tsuzuri Okada, Terence Stewart (C) 2018 All Rights Reserved. 
// Created: Sept. 19, 2018
// Last Updated: Sept. 19, 2018
// Version: 0.0.1A
// Description: 
//   This Class will represent the Game Application layer of the Blue Rapsol Engine
// *****************************************************************************

#include "BlueRapsolEngine.h"; 
#include "InitBlueRapsol.h" 
#include <iostream> 

//Macros

//300 MB in bytes
#define REQUIRED_STORAGE 314572800
//Temp macro for storage directory
#define STORAGE_DIRECTORY "c:\\"

//Name of this program for Mutex
#define MUTEX_APP_NAME "BlueRapsolEngineMutex"

void BlueRapsolEngine::Run() {

	//Initialization
	BlueRapsolEngine::Initialize();

	//TODO Program loop
}

void BlueRapsolEngine::Initialize() {
	InitBlueRapsol init;

	//System Check
	std::cout << "\nChecking if another instance of the application is running...\n";
	init.IsOnlyInstance(MUTEX_APP_NAME); //TODO terminate on false

	std::cout << "\nChecking System Memory...\n";
	init.ChkMem();
	init.ChkStorage(REQUIRED_STORAGE, STORAGE_DIRECTORY); //TODO terminate on false

	std::cout << "\nChecking CPU...\n";
	init.DisplayCPUArch();
	init.DisplayCPUSpeed();

	std::cout << "\nInitializing...\n";

	//Initialization
}
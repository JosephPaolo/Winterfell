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

void BlueRapsolEngine::run() {
	
	//Initialization
	BlueRapsolEngine::initialize();

	//TODO Program loop
}

void BlueRapsolEngine::initialize() {
	InitBlueRapsol init;

	std::cout << "Checking System Memory...\n";
	init.ChkMem();
	init.ChkStorage(REQUIRED_STORAGE, STORAGE_DIRECTORY);

	std::cout << "Initializing...\n";
}
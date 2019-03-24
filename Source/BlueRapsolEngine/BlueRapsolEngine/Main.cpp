//*************************************************************************** 
// File name: Main.cpp 
// Authors: Joseph Malibiran, Tsuzuri Okada, Terence Stewart (C) 2018 All Rights Reserved. 
// Created: Sept. 19, 2018
// Last Updated: Feb. 21, 2019
// Version: 0.1.0
// Description: 
//   This is the main function for the Blue Rapsol Game Engine.
// *****************************************************************************

#include <stdlib.h> 
#include "BlueRapsolEngine.h" 
#include "BlueRapsolApp.h" 

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) {
	// Enable run-time memory check for debug builds.
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

	try {
		BlueRapsolApp theGame(hInstance);

		OutputDebugString(L"Initializing Blue Rapsol Game...\n");
		if (!theGame.Initialize()) {
			return 0;
		}

		OutputDebugString(L"Starting Blue Rapsol Game...\n");
		theGame.Run(hInstance);
	}
	catch (...) {
		OutputDebugString(L"Exception Happened.\n");
	}

	//BlueRapsolEngine engineBR(hInstance);

	//Starting the engin
	//OutputDebugString(L"Starting Blue Rapsol Engine...\n");
	//engineBR.Run(hInstance); //Start engine
	return 0;
}
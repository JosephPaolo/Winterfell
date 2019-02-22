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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) {
	// Enable run-time memory check for debug builds.
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

	BlueRapsolEngine engineBR(hInstance);

	//Starting the engin
	OutputDebugString(L"Starting Blue Rapsol Engine...\n");
	engineBR.Run(hInstance); //Start engine

	//OutputDebugString(L"\n\nPress Enter to terminate application.\n");
	//std::getchar(); //Prevents program from terminating immediately by prompting for char user input
	return 0;
}
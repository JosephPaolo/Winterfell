//*************************************************************************** 
// File name: Main.cpp 
// Authors: Joseph Malibiran, Tsuzuri Okada, Terence Stewart (C) 2018 All Rights Reserved. 
// Created: Sept. 19, 2018
// Last Updated: Sept. 19, 2018
// Version: 0.0.1A
// Description: 
//   This is the main function for the Blue Rapsol Game Engine.
// *****************************************************************************

//#include <iostream> 
#include <stdlib.h> 
#include "BlueRapsolEngine.h" 
#include "../../DirectX/Common/d3dApp.h"

//TODO: Regarding maintaining one instance: figure out if we can substitute HINSTANCE hInstance in InitDirect3DApp::InitDirect3DApp(HINSTANCE hInstance) 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) {
	// Enable run-time memory check for debug builds.
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

	BlueRapsolEngine engineBR;
	//std::cout << "Starting Blue Rapsol Engine...\n";
	OutputDebugString(L"Starting Blue Rapsol Engine...\n");
	engineBR.Run(hInstance); //Start engine

	//std::cout << "\n\nPress Enter to terminate application.\n";
	OutputDebugString(L"\n\nPress Enter to terminate application.\n");
	std::getchar(); //Prevents program from terminating immediately by prompting for char user input
	return 0;
}
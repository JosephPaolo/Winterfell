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
//#include <iostream> 

//Macros

//300 MB in bytes
#define REQUIRED_STORAGE 314572800
//Temp macro for storage directory
#define STORAGE_DIRECTORY L"c:\\"

//Name of this program for Mutex
#define MUTEX_APP_NAME L"BlueRapsolEngineMutex"

void BlueRapsolEngine::Run(HINSTANCE hInstance) {

	//Initialization
	BlueRapsolEngine::Initialize(hInstance);

	//TODO Program loop. Move loop from d3dApp.cpp
	BlueRapsolEngine::GameLoop();

}

void BlueRapsolEngine::Initialize(HINSTANCE hInstance) {
	InitBlueRapsol init;
	//InitDirect3DApp d3d;

	//System Check
	//std::cout << "\nChecking if another instance of the application is running...\n";
	OutputDebugString(L"\nChecking if another instance of the application is running...\n");
	if (!init.IsOnlyInstance(MUTEX_APP_NAME)) {
		return;
	}

	//std::cout << "\nChecking System Memory...\n";
	OutputDebugString(L"\nChecking System Memory...\n");
	init.ChkMem();
	init.ChkStorage(REQUIRED_STORAGE, STORAGE_DIRECTORY); //TODO terminate on false

	//std::cout << "\nChecking CPU...\n";
	OutputDebugString(L"\nChecking CPU...\n");
	init.DisplayCPUArch();
	init.DisplayCPUSpeed();

	//Initialization
	//std::cout << "\nInitializing...\n";
	OutputDebugString(L"\nInitializing...\n");

	//init.InitializeD3d(hInstance);
}

//TODO transfer game loop here
//Not yet used because the game loop is in d3dApp.cpp
int BlueRapsolEngine::GameLoop() {
	MSG msg = { 0 };

	/*
	mTimer.Reset();

	while (msg.message != WM_QUIT)
	{
		// If there are Window messages then process them.
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// Otherwise, do animation/game stuff.
		else
		{
			mTimer.Tick();

			if (!mAppPaused)
			{
				CalculateFrameStats();
				Update(mTimer);
				Draw(mTimer);
			}
			else
			{
				Sleep(100);
			}
		}
	}
	*/
	return (int)msg.wParam;
}
//*************************************************************************** 
// File name: InitBlueRapsol.h
// Authors: Joseph Malibiran, Tsuzuri Okada, Terence Stewart (C) 2018 All Rights Reserved. 
// Created: Sept. 19, 2018
// Last Updated: Sept. 19, 2018
// Version: 0.0.1A
// Description: 
//   This is the header for InitBlueRapsol.cpp. This class is for initializing the Blue 
//   Rapsol game engine. It first makes hardware checks for compatibility and adjustments.
// *****************************************************************************

#pragma once

#include <windows.h>
#include <WinBase.h>
#include <stdlib.h> 
#include <string>
#include "../../BlueRapsolEngine/BlueRapsolEngine/KeyboardListener.h"
#include "../../BlueRapsolEngine/BlueRapsolEngine/MouseListener.h"
#include "../../DirectX/Framework/InitDirect3DApp.h"

class InitBlueRapsol{

public:
	//CONSTRUCTOR
	//InitBlueRapsol(HINSTANCE hInstance);

	//Check for multiple Instances
	bool IsOnlyInstance(LPCTSTR appName);

	//Check for sufficient storage space
	bool ChkStorage(unsigned long long requiredBytes, LPCWSTR directory);

	//Check for available RAM and virtual memory
	void ChkMem();

	//Display CPU speed and architecture
	void DisplayCPUArch();
	void DisplayCPUSpeed();

	//Initialize DirectX
	//TODO modify; TODO remove user input parameters
	int InitializeD3d(HINSTANCE hInstance);
};

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

class InitBlueRapsol{

public:
	//CONSTRUCTOR
	InitBlueRapsol();

	//TODO Check for multiple Instances
	bool IsOnlyInstance();

	//TODO Check for sufficient storage space
	bool ChkStorage(unsigned long long requiredBytes, const char* directory);

	//TODO Check for available RAM and virtual memory
	void ChkMem();

	//TODO Display CPU speed and architecture
	void DisplayCPUArch();
	void DisplayCPUSpeed();
};

//*************************************************************************** 
// File name: InitBRChkMem.cpp 
// Author: Created by Joseph Malibiran (C) 2018 All Rights Reserved. 
// Created: Sept. 19, 2018
// Last Updated: Sept. 19, 2018
// Version: 0.0.1A
// Description: 
//   These are functions of Class InitBlueRapsol. These are used to check and display 
//   available Storage, RAM and virtual memory. If there isn't atleast 300MB Storage 
//   space then notify user.
// *****************************************************************************

#include "InitBlueRapsol.h" 
#include <windows.h>
#include <WinBase.h>
#include <stdlib.h> 
#include <iostream> 
#include <string>

//Used in converting units of measurements from bytes
const LONGLONG toKB = 1024;
const LONGLONG toMB = 1024 * toKB;
const LONGLONG toGB = 1024 * toMB;

//Check for required Storage space, notify user on insufficient space
bool InitBlueRapsol::ChkStorage(unsigned long long requiredBytes, const char* directory) {
	ULARGE_INTEGER availableStorage;
	::GetDiskFreeSpaceEx(directory, &availableStorage, NULL, NULL);
	std::cout << "Available storage memory: " + std::to_string(availableStorage.QuadPart / toMB) + " MB\n";

	if ( availableStorage.QuadPart < requiredBytes ) {
		std::cout << "Insufficient storage space! You require at least " + std::to_string(requiredBytes / toMB) + "MB in storage space.\n";
		return false;
	}

	return true;
}

//Check and display RAM and Virtual memory
void InitBlueRapsol::ChkMem() {
	MEMORYSTATUSEX memStat;
	memStat.dwLength = sizeof(memStat); //Note: memStat.dwLength must be initialized before calling GlobalMemoryStatusEx()
	GlobalMemoryStatusEx(&memStat);

	//Display memory stats
	std::cout << "Available physical memory: " + std::to_string(memStat.ullAvailPhys / toMB) + " MB\n";
	std::cout << "Available virtual memory: " + std::to_string(memStat.ullAvailVirtual / toMB) + " MB\n";
}

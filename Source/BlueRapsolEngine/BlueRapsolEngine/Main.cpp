//*************************************************************************** 
// File name: Main.cpp 
// Authors: Joseph Malibiran, Tsuzuri Okada, Terence Stewart (C) 2018 All Rights Reserved. 
// Created: Sept. 19, 2018
// Last Updated: Sept. 19, 2018
// Version: 0.0.1A
// Description: 
//   This is the main function for the Blue Rapsol Game Engine.
// *****************************************************************************

#include <iostream> 
#include <stdlib.h> 
#include "BlueRapsolEngine.h" 

int main() {
	BlueRapsolEngine engineBR;
	std::cout << "Starting Blue Rapsol Engine...\n";
	engineBR.Run(); //Start engine

	std::cout << "\n\nPress Enter to terminate application.\n";
	std::getchar(); //Prevents program from terminating immediately by prompting for char user input
	return 0;
}
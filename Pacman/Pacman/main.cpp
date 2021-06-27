#include "Pacman.h"
#include <iostream>
#include<fstream>

using namespace std;


//Entry Point for Application
int main(int argc, char* argv[]) {

	//Here I ask the user to enter the cherry count
	int _cherryCount = 1;
	//cout << "How many munchies?" << endl;
	//cin >> _cherryCount;

	Pacman* game = new Pacman(argc, argv, _cherryCount); // here I passed the cherryCount into the Pacman class
}
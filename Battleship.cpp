#include "stdafx.h"
#include "Battleship.h"
#include <iostream>
#include <string>
using namespace std;

//creates a new battleship of correct size
Battleship::Battleship(int s, string n, char c)
{
	shipSize = s;
	shipName = n;
	numHits = 0;
	shipChar = c;
}

//return the size of the current ship
int Battleship::getSize()
{
	return shipSize;
}

//return the name of the current ship
string Battleship::getName()
{
	return shipName;
}

//set the location of the current ship
void Battleship::addHit()
{
	numHits++;
}

//If ship takes max hits, will sink
int Battleship::sinkShip()
{
	if (numHits == shipSize)
	{
		isSunk = true;
		cout << "You just sunk the " << getName() << endl;
		return 1;
	}

	return 0;
}

char Battleship::getShipChar()
{
	return shipChar;
}

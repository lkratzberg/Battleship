#pragma once
#include <string>
using namespace std;

class Battleship
{
private:
	int shipSize;
	string shipName;
	int numHits;
	bool isSunk;
	char shipChar;
public:
	Battleship(int, string, char);
	int getSize();
	string getName();
	void addHit();
	int sinkShip();
	char getShipChar();
};

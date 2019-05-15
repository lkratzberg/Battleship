#include "pch.h"
#include "BattleshipThing.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

int noShips = 5;

BattleshipThing carrier(5, "Carrier", 'A');
BattleshipThing cruiser(4, "Cruiser", 'C');
BattleshipThing destroyer(3, "Destroyer", 'D');
BattleshipThing submarine(3, "Submarine", 'S');
BattleshipThing boat(2, "Boat", 'B');

//prototypes
void fillBoard(char board[][10]);
void placeShips(char playerBoard[10][10], BattleshipThing& ship);
void printBoard(char board[][10]);
char guess(char board[][10], char playerBoard[][10]);
void guessAI(char board[][10], char playerBoard[][10], int& guessY, int& guessX);
void shipLookup(char playerBoard[10][10], int& guessY, int& guessX);

int main()
{
	int guessY;
	int guessX;
	srand(time(0));
	char board[10][10];
	char playerBoard[10][10];
	
	
	fillBoard(board);
	fillBoard(playerBoard);
	placeShips(playerBoard, carrier);
	placeShips(playerBoard, cruiser);
	placeShips(playerBoard, destroyer);
	placeShips(playerBoard, submarine);
	placeShips(playerBoard, boat);
	printBoard(board);
	cout << endl;
	printBoard(playerBoard);
	


	//guess(board, playerBoard);
	printBoard(board);

	while (noShips > 0)
	{
		guessAI(board, playerBoard, guessY, guessX);
		cout << noShips;
		printBoard(board);
	}
}

void fillBoard(char board[][10])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			board[i][j] = '*';
		}
	}
}

void placeShips(char playerBoard[10][10], BattleshipThing& ship)
{
	int x = rand() % 10;
	int y = rand() % 10;
	bool isOkay = false;
	bool gameOver = false;
	int direction = 0;


	//if direction is 0 ship goes left
	while (!isOkay)
	{
		direction = rand() % 2;
		x = rand() % 10;
		y = rand() % 10;
		cout << ship.getName() << endl;
		cout << x << ", " << y << endl;
		cout << "Direction: " << direction << endl;

		if (direction == 0)
		if (y - ship.getSize() < -1)
			isOkay = false;
		else
		{
			int temp = y;
			int i = 0;
			isOkay = true;
			while (isOkay && i < ship.getSize())
			{
				if (playerBoard[x][temp] == '*')
				{
					isOkay = true;
					temp--;
				}
				else
				{
					isOkay = false;
				}
				i++;
			}
			if (isOkay)
			{
				for (int i = 0; i < ship.getSize(); i++)
				{
					playerBoard[x][y] = ship.getShipChar();
					y--;
				}
			}
		}
		if (direction == 1)
		{
			if (x - ship.getSize() < -1)
				isOkay = false;
			else
			{
				int temp = x;
				int i = 0;
				isOkay = true;
				while (isOkay && i < ship.getSize())
				{
					if (playerBoard[temp][y] == '*')
					{
						isOkay = true;
						temp--;
					}
					else
					{
						isOkay = false;
					}
					i++;
				}
				if (isOkay)
				{
					for (int i = 0; i < ship.getSize(); i++)
					{
						playerBoard[x][y] = ship.getShipChar();
						x--;
					}
				}
			}
		}
	}
}

void printBoard(char board[][10])
{
	cout << "    A B C D E F G H I J" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << left << setw(3) << i + 1;
		for (int j = 0; j < 10; j++)
		{
			cout << right << setw(2) << board[i][j];
		}
		cout << endl;
	}
}

char guess(char board[][10], char playerBoard[][10])
{
	char guess;
	int guess2;
	cout << "Enter your guess: ";
	cin >> guess >> guess2;

	if (playerBoard[guess2 - 1][guess - 65] != '*')
	{
		board[guess2 - 1][guess - 65] = 'H';
		return playerBoard[guess2 - 1][guess - 65];
	}
		
	else
	{
		board[guess2 - 1][guess - 65] = 'M';
		return 'M';
	}
		
}

void guessAI(char board[][10], char playerBoard[][10], int& guessY, int& guessX)
{
	int direction1;
	int direction2;
	int originY;
	int originX;

	guessY = rand() % 10;
	guessX = rand() % 10;
	originY = guessY;
	originX = guessX;

	/*
	if (playerBoard[guessY][guessX] != '*' && board[guessY][guessX] == '*')
	{
		board[guessY][guessX] = 'H';
		direction1 = rand() % 2;
		direction2 = rand() % 2;
		cout << direction1;
		cout << direction2;
		if (direction1 == 0)
		{
			if (direction2 == 0)
			{
				while (playerBoard[guessY][guessX] != '*')
				{
					board[guessY][guessX] = 'H';
					guessY += direction2;
					direction2 = -1;
				}
				if (playerBoard[guessY][guessX] == '*')
				{
					board[guessY][guessX] = 'M';
					guessY = originY;
					direction2 = 1;
				}
			}
			if (direction2 == 1)
			{
				while (playerBoard[guessY][guessX] != '*')
				{
					board[guessY][guessX] = 'H';
					guessY += direction2;
				}
				guessY = originY;
				if (playerBoard[guessY][guessX] == '*')
				{
					board[guessY][guessX] = 'M';
					guessY = originY;
					direction1 = 1;
				}
			}
		}

		if (direction1 == 1)
		{
			if (direction2 == 0)
			{
				cout << direction1;
				while (playerBoard[guessY][guessX] != '*')
				{
					board[guessY][guessX] = 'H';
					guessX += direction2;
					direction2 = -1;
				}
				if (playerBoard[guessY][guessX] != '*')
				{
					guessX = originX;
					direction2 = 1;
				}
			}
			if (direction2 == 1)
			{
				while (playerBoard[guessY][guessX] != '*')
				{
					board[guessY][guessX] = 'H';
					guessX += direction2;
				}
			}
			if (direction1 == 0)
			{
				if (direction2 == 0)
				{
					while (playerBoard[guessY][guessX] != '*')
					{
						board[guessY][guessX] = 'H';
						//return(playerBoard[guessY][guessX]);
						guessY += direction2;
						direction2 = -1;
					}
					if (playerBoard[guessY][guessX] == '*')
					{
						board[guessY][guessX] = 'M';
						guessY = originY;
						direction2 = 1;
					}
				}
				if (direction2 == 1)
				{
					while (playerBoard[guessY][guessX] != '*')
					{
						board[guessY][guessX] = 'H';
						guessY += direction2;
					}
					guessY = originY;
					if (playerBoard[guessY][guessX] == '*')
					{
						board[guessY][guessX] = 'M';
						guessY = originY;
						direction1 = 1;
					}
				}
			}
		}
	}
	*/

	//new
	if (playerBoard[guessY][guessX] != '*' && board[guessY][guessX] == '*')
	{
		//Vertical Down
		while (playerBoard[guessY][guessX] != '*')
		{
			board[guessY][guessX] = 'H';
			guessY += 1;
			shipLookup(playerBoard, guessY, guessX);
		}
		cout << noShips;
		if (playerBoard[guessY][guessX] == '*')
		{
			board[guessY][guessX] = 'M';
			guessY = originY;
		}
		//Vertical Up
		while (playerBoard[guessY][guessX] != '*')
		{
			board[guessY][guessX] = 'H';
			guessY -= 1;
			shipLookup(playerBoard, guessY, guessX);
		}
		cout << noShips;
		if (playerBoard[guessY][guessX] == '*')
		{
			board[guessY][guessX] = 'M';
			guessY = originY;
		}
		//Horizontal Right
		while (playerBoard[guessY][guessX] != '*')
		{
			board[guessY][guessX] = 'H';
			guessX += 1;
			shipLookup(playerBoard, guessY, guessX);
		}
		cout << noShips;
		if (playerBoard[guessY][guessX] == '*')
		{
			board[guessY][guessX] = 'M';
			guessX = originX;
		}
		//Horizontal Left
		while (playerBoard[guessY][guessX] != '*')
		{
			board[guessY][guessX] = 'H';
			guessX -= 1;
			shipLookup(playerBoard, guessY, guessX);
		}
		cout << noShips;
		if (playerBoard[guessY][guessX] == '*')
		{
			board[guessY][guessX] = 'M';
			guessX = originY;
		}
	}
	
	if (playerBoard[guessY][guessX] == '*')
	{
		board[guessY][guessX] = 'M';
	}
}

void shipLookup(char playerBoard[10][10], int& guessY, int& guessX)
{
	switch (playerBoard[guessY][guessX])
	{
	case 'A':
		carrier.addHit();
		noShips -= carrier.sinkShip();
		break;
	case 'B':
		boat.addHit();
		noShips -= boat.sinkShip();
		cout << boat.getHits();
		break;
	case 'C':
		cruiser.addHit();
		noShips -= cruiser.sinkShip();
		break;
	case 'D':
		destroyer.addHit();
		noShips -= destroyer.sinkShip();
		break;
	case 'S':
		submarine.addHit();
		noShips -= submarine.sinkShip();
		break;
	default:
		break;
	}
}

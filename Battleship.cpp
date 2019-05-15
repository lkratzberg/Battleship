#include "stdafx.h"
#include "Battleship.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

const int BOARD_SIZE = 10;

void fillBoard(char board[][BOARD_SIZE]);
void placeShips(char board[][BOARD_SIZE], Battleship& ship);
char guess(char board[][BOARD_SIZE], char playerBoard[][BOARD_SIZE]);
void AIguess(char board[][BOARD_SIZE], char playerBoard[][BOARD_SIZE], 
	int& direction1, int& direction2, bool& isHit);
void keepGuessing(char board[][BOARD_SIZE], char playerBoard[][BOARD_SIZE], 
	int guessRow, int guessCol, bool& isHit, int& direction2);
void setDirections(int& direction1, int& direction2);
void keepScore(char board[][BOARD_SIZE], char playerBoard[][BOARD_SIZE],
	Battleship& ship, int& noShips);
void printBoard(char board[][BOARD_SIZE]);

int main()
{
	srand(time(0)); 
	char board[BOARD_SIZE][BOARD_SIZE];
	char playerBoard[BOARD_SIZE][BOARD_SIZE];
	int noShips = 5;
	int direction1;
	int direction2;
	bool isHit = false;
	
	Battleship carrier(5, "Aircraft Carrier", 'A');
	Battleship cruiser(4, "Cruiser", 'C');
	Battleship destroyer(3, "Destroyer", 'D');
	Battleship submarine(3, "Submarine", 'S');
	Battleship boat(2, "Boat", 'B');

	fillBoard(board);
	fillBoard(playerBoard);
	placeShips(playerBoard, carrier);
	placeShips(playerBoard, cruiser);
	placeShips(playerBoard, destroyer);
	placeShips(playerBoard, submarine);
	placeShips(playerBoard, boat);

	cout << "Board for viewing: " << endl;
	printBoard(board);
	cout << endl << endl << "Board with ships: " << endl;
	printBoard(playerBoard);
	cout << endl << endl << "Let's Play!" << endl;
	
	

	return 0;
}

void fillBoard(char board[][BOARD_SIZE])
{
	//fill every cell in board to initialize
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			board[i][j] = '*';
		}
	}	
}

void placeShips(char board[][BOARD_SIZE], Battleship& ship)
{
	//select random coordinate for placement
	int x = rand() % 10;
	int y = rand() % 10;

	//check if ship is already there & it will fit
	bool isOkay = false;
	int direction = 0;

	while (!isOkay)
	{
		direction = rand() % 2;
		x = rand() % 10;
		y = rand() % 10;
		
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
					if (board[x][temp] == '*')
					{
						isOkay = true;
						temp--;
						i++;
					}
					else
					{
						isOkay = false;
					}
				}
				if (isOkay)
				{
					for (int i = 0; i < ship.getSize(); i++)
					{
						board[x][y] = ship.getShipChar();
						y--;
					}
				}

			}
		if (direction == 1)
			if (x - ship.getSize() < -1)
				isOkay = false;
			else
			{
				int temp = x;
				int i = 0;
				isOkay = true;
				while (isOkay && i < ship.getSize())
				{
					if (board[temp][y] == '*')
					{
						isOkay = true;
						temp--;
						i++;
					}
					else
					{
						isOkay = false;
					}
				}
				if (isOkay)
				{
					for (int i = 0; i < ship.getSize(); i++)
					{
						board[x][y] = ship.getShipChar();
						x--;
					}
				}

			}
	}
}

char guess(char board[][BOARD_SIZE], char playerBoard[][BOARD_SIZE])
{
	char guess;
	int guess2;
	cout << "Enter your guess (Ex: A2): " << endl;
	cin >> guess >> guess2;

	//need rule for if they guess something off the board
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

//computer generated guesses 
void AIguess(char board[][BOARD_SIZE], char playerBoard[][BOARD_SIZE], int& direction1, int& direction2, bool& isHit)
{
	int guessRow = rand() % 10;
	int guessCol = rand() % 10;
	int originRow = guessRow;
	int originCol = guessCol;
	
	//if hit
	if (playerBoard[guessRow][guessCol] != '*')
	{
		board[guessRow][guessCol] = 'H';
		isHit = true;
		
		setDirections(direction1, direction2);
		cout << endl << "Direction 1: " << direction1 << endl;
		cout << endl << "Direction 2: " << direction2 << endl;
		if (direction1 == 0) //if 0 - this means up/down
		{
			if (direction2 == -1) //direction is up
			{
				guessCol = originCol + direction2;
				keepGuessing(board, playerBoard, guessRow, guessCol, isHit, direction2);
					
				direction2 = 1; //change direction to go down
				guessCol = originCol + direction2;
				keepGuessing(board, playerBoard, guessRow, guessCol, isHit, direction2);
			}
			if (direction2 == 1) //direction is down
			{
				guessCol = originCol + direction2;
				keepGuessing(board, playerBoard, guessRow, guessCol, isHit, direction2);
						
				direction2 = -1; //change direction to go up
				guessCol = originCol + direction2;
				keepGuessing(board, playerBoard, guessRow, guessCol, isHit, direction2);
			}
		}
		
		if (direction1 == 1) //if 0 - this means right/left
		{
			if (direction2 == -1) //direction is left
			{
				guessRow = originRow + direction2;
				keepGuessing(board, playerBoard, guessRow, guessCol, isHit, direction2);
				
				direction2 = 1;  //change direction to right
				guessRow = originRow + direction2;
				keepGuessing(board, playerBoard, guessRow, guessCol, isHit, direction2);
			}
			if (direction2 == 1) //direction is right
			{
				guessRow = originRow + direction2;
				keepGuessing(board, playerBoard, guessRow, guessCol, isHit, direction2);
				
				direction2 = -1; //change direction to left
				guessRow = originRow + direction2;
				keepGuessing(board, playerBoard, guessRow, guessCol, isHit, direction2);
			}
			
		}
	}
	else //not hit
	{
		board[guessRow][guessCol] = 'M';
	}
}

void keepGuessing(char board[][BOARD_SIZE], char playerBoard[][BOARD_SIZE], int guessRow, int guessCol, bool& isHit, int& direction2)
{
	if (playerBoard[guessRow][guessCol] != '*')
	{
		isHit = true;
		while (isHit) //if hit, keep going in same direction
		{
			if (playerBoard[guessRow][guessCol] != '*')
			{
				board[guessRow][guessCol] = 'H';
				isHit = true;
				guessCol += direction2;
				printBoard(board);
			}
			else
			{
				isHit = false;
				printBoard(board);
			}
				
		}
	}	
}

void setDirections(int& direction1, int& direction2)
{
	direction1 = rand() % 2; //pick random direction(0 or 1)
	
	direction2 = rand() % 2; //pick random direction (0 above, 1 below OR 0 left, 1 right)
	if (direction2 == 0)
		direction2 = -1;
}

void keepScore(char board[][BOARD_SIZE], char playerBoard[][BOARD_SIZE], 
	Battleship& ship, int& noShips)
{
	

}

void printBoard(char board[][BOARD_SIZE])
{
	cout << "    A B C D E F G H I J" << endl;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		cout << left << setw(3) << i+1;
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			cout << right << setw(2) << board[i][j];
		}
		cout << endl;
	}
}

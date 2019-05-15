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
char guess(char board[][BOARD_SIZE], char solution1Board[][BOARD_SIZE]);
void AIguess(char board[][BOARD_SIZE], char solution1Board[][BOARD_SIZE], 
	int& direction1, int& direction2, bool& isHit);
void keepGuessing(char board[][BOARD_SIZE], char solution1Board[][BOARD_SIZE], 
	int guessRow, int guessCol, bool& isHit, int& direction2);
void setDirections(int& direction1, int& direction2);
void keepScore(char board[][BOARD_SIZE], char solution1Board[][BOARD_SIZE],
	Battleship& ship, int& noShips);
void printBoard(char player1Board[][BOARD_SIZE], char player2Board[][BOARD_SIZE]);

int main()
{
	srand(time(0)); 
	
	char player1Board[BOARD_SIZE][BOARD_SIZE]; //actual person player's board
	char player2Board[BOARD_SIZE][BOARD_SIZE]; //computer player's board
	char solution1Board[BOARD_SIZE][BOARD_SIZE]; //person's solution board
	char solution2Board[BOARD_SIZE][BOARD_SIZE]; //computer player's solution board
	
	int noShips = 5;
	int direction1;
	int direction2;
	bool isHit = false;
	string playerName;
	
	Battleship carrier1(5, "Aircraft Carrier", 'A');
	Battleship cruiser1(4, "Cruiser", 'C');
	Battleship destroyer1(3, "Destroyer", 'D');
	Battleship submarine1(3, "Submarine", 'S');
	Battleship boat1(2, "Boat", 'B');

	Battleship carrier2(5, "Aircraft Carrier", 'A');
	Battleship cruiser2(4, "Cruiser", 'C');
	Battleship destroyer2(3, "Destroyer", 'D');
	Battleship submarine2(3, "Submarine", 'S');
	Battleship boat2(2, "Boat", 'B');

	fillBoard(player1Board);
	fillBoard(player2Board);
	fillBoard(solution1Board);
	fillBoard(solution2Board);
	
	placeShips(solution1Board, carrier1);
	placeShips(solution1Board, cruiser1);
	placeShips(solution1Board, destroyer1);
	placeShips(solution1Board, submarine1);
	placeShips(solution1Board, boat1);
	placeShips(solution2Board, carrier2);
	placeShips(solution2Board, cruiser2);
	placeShips(solution2Board, destroyer2);
	placeShips(solution2Board, submarine2);
	placeShips(solution2Board, boat2);

	cout << "************************** Battleship **************************" << endl;
	cout << "Enter player's name: " << endl;
	cin >> playerName;

	cout << "Player will enter a coordinate to try to \"hit\" the ship." << endl
		<< "The computer play will occur right after automatically." << endl
		<< "The first player to sink all 5 ships wins." << endl << endl;
	cout << endl << endl << "Let's Play!" << endl << endl;

	cout << endl << "****** " << playerName << "'s Board ******" 
		<< "          "
		<< "****** Computer's Board ******" << endl;
	
	printBoard(player1Board, player1Board);
	
	//ask user to input their play
	//computer plays immediately after - only 1 play, how will this happen?
	

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

char guess(char board[][BOARD_SIZE], char solution1Board[][BOARD_SIZE])
{
	char guess;
	int guess2;
	cout << "Enter your guess (Ex: A2): " << endl;
	cin >> guess >> guess2;

	//need rule for if they guess something off the board
	if (solution1Board[guess2 - 1][guess - 65] != '*')
	{
		board[guess2 - 1][guess - 65] = 'H';
		return solution1Board[guess2 - 1][guess - 65];
	}	
	else
	{
		board[guess2 - 1][guess - 65] = 'M';
		return 'M';
	}	
}

//computer generated guesses 
void AIguess(char board[][BOARD_SIZE], char solution1Board[][BOARD_SIZE], int& direction1, int& direction2, bool& isHit)
{
	int guessRow = rand() % 10;
	int guessCol = rand() % 10;
	int originRow = guessRow;
	int originCol = guessCol;
	
	//if hit
	if (solution1Board[guessRow][guessCol] != '*')
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
				keepGuessing(board, solution1Board, guessRow, guessCol, isHit, direction2);
					
				direction2 = 1; //change direction to go down
				guessCol = originCol + direction2;
				keepGuessing(board, solution1Board, guessRow, guessCol, isHit, direction2);
			}
			if (direction2 == 1) //direction is down
			{
				guessCol = originCol + direction2;
				keepGuessing(board, solution1Board, guessRow, guessCol, isHit, direction2);
						
				direction2 = -1; //change direction to go up
				guessCol = originCol + direction2;
				keepGuessing(board, solution1Board, guessRow, guessCol, isHit, direction2);
			}
		}
		
		if (direction1 == 1) //if 0 - this means right/left
		{
			if (direction2 == -1) //direction is left
			{
				guessRow = originRow + direction2;
				keepGuessing(board, solution1Board, guessRow, guessCol, isHit, direction2);
				
				direction2 = 1;  //change direction to right
				guessRow = originRow + direction2;
				keepGuessing(board, solution1Board, guessRow, guessCol, isHit, direction2);
			}
			if (direction2 == 1) //direction is right
			{
				guessRow = originRow + direction2;
				keepGuessing(board, solution1Board, guessRow, guessCol, isHit, direction2);
				
				direction2 = -1; //change direction to left
				guessRow = originRow + direction2;
				keepGuessing(board, solution1Board, guessRow, guessCol, isHit, direction2);
			}
			
		}
	}
	else //not hit
	{
		board[guessRow][guessCol] = 'M';
	}
}

void keepGuessing(char board[][BOARD_SIZE], char solution1Board[][BOARD_SIZE], int guessRow, int guessCol, bool& isHit, int& direction2)
{
	if (solution1Board[guessRow][guessCol] != '*')
	{
		isHit = true;
		while (isHit) //if hit, keep going in same direction
		{
			if (solution1Board[guessRow][guessCol] != '*')
			{
				board[guessRow][guessCol] = 'H';
				isHit = true;
				guessCol += direction2;
				
			}
			else
			{
				isHit = false;
				
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

void keepScore(char board[][BOARD_SIZE], char solution1Board[][BOARD_SIZE], 
	Battleship& ship, int& noShips)
{
	

}

void printBoard(char player1Board[][BOARD_SIZE], char player2Board[][BOARD_SIZE])
{
	cout << "    A B C D E F G H I J" << "               " << "    A B C D E F G H I J" << endl;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		cout << left << setw(3) << i+1; //print player's board
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			cout << right << setw(2) << player1Board[i][j];
		}
		cout << "               ";
		cout << left << setw(3) << i + 1; //print computer's board
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			cout << right << setw(2) << player2Board[i][j];
		}

		cout << endl;
	}
}

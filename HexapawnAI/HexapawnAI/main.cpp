/*
	Created by: James Abitria
	Project Name: Hexapawn AI
	Date Created: 6-7-24
	Last Update: 6-23-24
	
	Description: This program runs the game Hexapawn, a game on a 3x3 chess board consisting of 3 pawns on the first and last rank.
	The goal of the game is to get a pawn to the other side of the board, capture all enemy pawns, or leave the opponent with no legal move.
	The program implements a basic AI that will play stronger the longer the player plays against it. The game will keep track of score 
	with each game.
*/
#include "Game.hpp"

// Initializes the random move choices and instantiates the game.
int main() {
	srand(time(NULL));
	Game g;

	g.playGame();
	return 0;
}
#include "Tree.hpp"
#include "Pawn.hpp"

class Game {
public:
	/*
		Function: Game
		Constructor Parameters: None

		Description: Initializes the game state, placing all the player's pawn on row 2, then initializes the other two rows of the board
		with the computer's pawns and the blank spaces.
	*/
	Game();

	/*
		Function: playGame
		
		Description: Runs the gameplay of Hexapawn, including invoking file reading, giving the player options for moves, and prompting the
		computer to make its move. Each game runs until a win condition in met for either player, tracking the amount of wins until the player
		decides to end the game. The AI of the computer will improve at the end of each player victory.
	*/
	void playGame();
private:
	void populateTree(int tree);
	string readToCharacter(string line, int& reference);
	void printBoard();
	void updateBoard();
	void printOptions();
	void travelTree();
	TreeNode* makeComputerMove();
	bool checkPush(int pawn);
	bool checkLeft(int pawn);
	bool checkRight(int pawn);
	void moveOptions(int pawn);
	bool checkPlayerWin();
	bool checkCpuWin();
	void resetGame();

	Tree board1, board2, board3;
	TreeNode* currentPosition;
	Pawn playerPawns[3];
	char curBoard[3][3];
};
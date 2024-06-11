#include "Tree.hpp"
#include "Pawn.hpp"

class Game {
public:
	Game();
	void playGame();
	void populateTree(int tree);
private:
	string readToCharacter(string line, int& reference);
	void printBoard();
	void updateBoard();
	void printOptions();

	Tree board1, board2, board3;
	Pawn playerPawns[3];
	Pawn enemyPawns[3];
	char curBoard[3][3];
	bool legalPushes[3];
	bool legalCaptures[6];
};
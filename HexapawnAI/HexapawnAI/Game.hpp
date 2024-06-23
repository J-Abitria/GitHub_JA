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
	bool legalPushes[3];
	bool legalCaptures[6];
};
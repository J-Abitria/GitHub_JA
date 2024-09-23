#include "Game.hpp"
#include "Test.hpp"
/*
	Created by: James Abitria, Nick Haugen, Zach Goodin, Nick Rausch
	Class: CPT_S 122
	Lab Sections: 6 (James),
	Assignment: Programming Assignment 9
	Date Created: 4-12-24
	Last Update: 4-22-24

	Name: Hold the Place
	Description: This program runs a Tower Defense game, with a simple path that enemies travel across to enter a portal to deal damage to
	the Player. The Player must place Towers using left-click in order to destroy all enemies and win the game. There is currently a single
	wave.
*/
int main() {
	Test t;
	Game g;

	t.runTests();
	system("cls");
	g.runGame();
	return 0;
}
#pragma once
#include <iostream>
#include "Prisoner.h"
#include "Strategy.h"
#include "StrategyGenerator.h"
#include "Matrix.h"

/**
Game Class - Takes 2 Stategies and runs a game of n iterations against each other. It stores and returns the resulting sentences
**/

class Game										
{
public:
	Game();
	Game(string fileA, string fileB);						// Takes two filenames for strategies to use in this given game.
	virtual ~Game();
	virtual void find_outcome(int iteration);				// Finds both the decisions of the prisoners for given iteration and sentences them accordingly.
	virtual void run(int iterations);						// Runs the game with a given amount of iterations. It will take the filenames given in instatiation to use as strategies.					
	virtual Matrix<int> * getResults();						// Returns the total sentences for each prisoner for this given game. 0 - Prisoner A, 1 - Prisoner B
protected:
	int iteration;
	Prisoner * A;
	Prisoner * B;
	Strategy * stratA;
	Strategy * stratB;
	Matrix<int> * totalResults;
};




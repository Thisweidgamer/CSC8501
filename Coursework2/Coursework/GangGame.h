#pragma once
#include "Game.h"

enum class Decision;
class Gang;
enum method;

class GangGame :
	public Game
{
public:
	GangGame(string givenstrat, vector<string> strategies);
	~GangGame();
	void find_outcome(int iteration);				// Finds both the decisions of the prisoners for given iteration and sentences them accordingly.
	void run(int iterations,method mthd);			// Runs the game with a given amount of iterations. It will take the filenames given in instatiation to use as strategies.
	bool spyGame(bool spy_A, bool spy_B, method mthd);
protected:
	int iteration;
	Gang * gangA;
	Gang * gangB;
};


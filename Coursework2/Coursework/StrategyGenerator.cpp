#include "StrategyGenerator.h"
#include <fstream>
#include <time.h>

StrategyGenerator::StrategyGenerator()
{
}


StrategyGenerator::~StrategyGenerator() {
	//terminate_tree(&root);
}


void StrategyGenerator::generateStrategy(int lines, string file) {
	// A BETRAY,SILENCE or RANDOM must be accessable through a previous line or an if statement
	cout << "Generating Strategy for file: " << file << "\n";
	if (root) { 
		terminate_tree(&root); 
		all_lines.clear();
	}
	root = nullptr;
	generateLine(&root, 0, lines);

	toFile(file, lines);
}


void StrategyGenerator::toFile(string file, int lines) {
	ofstream outFile;
	outFile.open(file);

	for (int i = 0; i < lines; ++i) {
		if (all_lines[i] != "") {
			outFile << all_lines[i] << "\n";
		}
	}

	outFile.close();
}


void StrategyGenerator::generateLine(line ** tree, int lineno, int lines) 
{	//Generates the Binary Tree which stores the lines and logic of the generated strategy. 

	all_lines.resize(lines);

	// Only generate a line if it doesn't already exist. This means the tree won't be fully populated, however it is only used for logic purposes and does not need to be complete
	if (all_lines[lineno] == "") 
	{
		int randomCmd;

		if (lineno == 0) { randomCmd = 0; }										// If on first line - Pick if statement
		else if (lineno < lines - 2)											// If between first and third to last line, randomly choose the command.
		{	
			// choose a random number from 0,1,2,3. If the number is 0 generate an IF statement. This control frequency of IF statements
			int randomChoice = rand() % 4;
			if (randomChoice == 0) { randomCmd = 0; }
			// if we don't have an if statement pick a random outcome of BETRAY, SILENCE, RANDOM
			else { randomCmd = 1 + (rand() % 3); }
		}
		else { randomCmd = 1 + (rand() % 3); }									// If we are on the last or second last line, don't create if statement

		string cmd = commands[randomCmd];

		// Make sure the Tree we are trying to build exists
		if (!(*tree)) {
			*tree = new line;
			(*tree)->lineno = lineno;
		}

		if (cmd == "IF") 
		{	// Generate an if statement starting with the line number selected for it
			string statement = to_string(lineno) + " " + generateIf();
			// Select a random line to jump to and append the GOTO statement
			int gotoline = lineno+2 + (rand() % (lines-lineno-2));
			statement.append("GOTO " + to_string(gotoline));

			// Set up the children of the node and set up their line numbers
			(*tree)->command = statement;
			(*tree)->next = new line;
			(*tree)->jump = new line;

			(*tree)->next->lineno = lineno + 1;
			(*tree)->jump->lineno = gotoline;

			// Save this generated lines in the vector that stores all lines (for printing to file)
			all_lines[lineno] = statement;

			// Recursively generate the lines that are accessed by this IF statement (the next line and the one it jumps to)
			generateLine(&((*tree)->next), lineno + 1, lines);
			generateLine(&((*tree)->jump), gotoline, lines);
		}
		else if (cmd == "BETRAY" || cmd == "SILENCE" || cmd == "RANDOM") 
		{	// If it is one of the decision commands then the node will have no children.
			(*tree)->command = to_string(lineno) + " " + cmd;
			(*tree)->next = nullptr;
			(*tree)->jump = nullptr;

			all_lines[lineno] = (*tree)->command;
		}
	}
	else 
	{	// If the line does already exist then just set up a node without children
		(*tree)->command = all_lines[lineno];
		(*tree)->next = nullptr;
		(*tree)->jump = nullptr;

	}
}


string StrategyGenerator::generateIf() 
{	// Generate an if statement for the strategy
	string line = "IF ";
	int randomChoice = rand() % 2;

	if (randomChoice == 0)														// Choose nrvariables
	{ 
		// Select number variables to compare against each other
		string randomVar = nrvars[rand() % nrvars.size()];
		string randomOp = comparisonOps[rand() % 3];
		string randomVar2 = nrvars[rand() % nrvars.size()];

		// If it selected NUMBER then select a random number between 0 and 200
		if (randomVar == "NUMBER") { randomVar = to_string(rand() % 201); }
		if (randomVar2 == "NUMBER") { randomVar2 = to_string(rand() % 201); }
		
		// Add the condition to the line
		line.append(randomVar + " " + randomOp + " " + randomVar2 + " ");
	}
	else																		// Choose outcome variable
	{	
		// Select a random outcome variable
		string randomVar = outcomevars[rand() % outcomevars.size()];

		// Add condition to the line
		line.append("LASTOUTCOME = " + randomVar + " ");
	}

	return line;
}


void StrategyGenerator::terminate_tree(line ** tree) 
{
	if (*tree) 
	{
		if (&((*tree)->next))
			terminate_tree(&((*tree)->next));
		if (&((*tree)->jump))
			terminate_tree(&((*tree)->jump));

		delete (*tree)->next;
		delete (*tree)->jump;
		(*tree)->next = nullptr;
		(*tree)->jump = nullptr;

		delete (*tree);
		*tree = nullptr;
	}
}
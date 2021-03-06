#pragma once
#include <string>
#include <vector>

using namespace std;

enum class Decision {BETRAY,SILENCE};

// Operator overloading for the Decision enum class that allows printing out a decision
inline ostream& operator<<(ostream& ostr, Decision& result) {
	switch (result) {
	case Decision::BETRAY:
		ostr << "Betray";
		break;
	case Decision::SILENCE:
		ostr << "Silence";
		break;
	}
	return ostr;
}

// Forward declaration of the prisoner class
class Prisoner;

// Struct to store a variable that might either be an int or a string
struct vars {
	int intvar = NULL;
	string stringvar = "";
};



class Strategy {
protected:
	// protected variables
	string file;
	int currentline;

	struct node {
		node * left;
		node * right;
		int lineno;
		vector<string> command;
	};
	node * root = nullptr;

	vector<int> linenos;
	vector<string> lines;

	// List of possible tokens that are allowed in the Strategy files
	vector<string> tokens = { "IF","BETRAY","SILENCE","RANDOM","+","-",">","<","=","GOTO","ALLOUTCOMES_W","ALLOUTCOMES_X","ALLOUTCOMES_Y","ALLOUTCOMES_Z","W","X","Y","Z","LASTOUTCOME","ITERATIONS","MYSCORE"," ","0","1","2","3","4","5","6","7","8","9" };

	// protected functions
	void terminate_tree(node ** tree);
	bool checkvar(string var);
	vars getvar(string var, Prisoner A);
	Decision decide(node ** tree, Prisoner A);
	
public:
	Strategy();
	~Strategy();
	Strategy(const Strategy &strat);
	void terminate();
	void read(string filename);
	void interpret();
	void interpret_line(int i, node ** tree);
	bool ifstatement(string var1, char op, string var2, Prisoner prisoner);
	Decision decide_result(Prisoner A);
	string getFile();
};
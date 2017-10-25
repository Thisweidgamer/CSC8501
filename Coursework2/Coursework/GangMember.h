#pragma once
#include "Prisoner.h"
class GangMember :
	public Prisoner
{
public:
	enum Outcome {A,B,C,W,X,Y,Z};
	GangMember();
	~GangMember();
	int get_allA();
	int get_allB();
	int get_allC();
	bool isLeader();
	bool isSpy();
	void makeLeader();
	void makeSpy();
	virtual void sentence(Outcome outcome);
	virtual string get_last_outcome();
protected:
	int alloutcomes_a;
	int alloutcomes_b;
	int alloutcomes_c;
	bool is_leader = false;
	bool is_spy = false;

	Outcome last_outcome;
};


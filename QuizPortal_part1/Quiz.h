#pragma once

#include "stdafx.h"

using namespace std;

class Quiz {
public:
/*-- Getter/Setter -----------------------*/
	int Get_Point();
	int Get_Difficulty();
	string Get_Context1();
	string Get_Context2();
	int Get_typeNumber();
	string Get_Answer();

	void Set_Point(int);
	void Set_Difficulty(int);
	void Set_Context1(string);
	void Set_Context2(string);
	void Set_typeNumber(int);
	void Set_Answer(string);

/*-- Constructor/Destructor --------------*/
	Quiz();
	Quiz(int ,int);
	~Quiz();

private:
/*-- Instance ----------------------------*/
	int typeNumber;
	string context1;
	string context2;
	string answer;
	int point;
	int difficulty;
};

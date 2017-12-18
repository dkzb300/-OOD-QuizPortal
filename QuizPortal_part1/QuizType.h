#pragma once

#include "stdafx.h"

using namespace std;

class QuizType {
public:
/*-- Getter/Setter -----------------------*/
	string Get_typeName();
	int Get_openContext2();
	int Get_numberOfAnswer();
	char Get_answerType();

	void Set_typeName(string);
	void Set_openContext2(int);
	void Set_numberOfAnswer(int);
	void Set_answerType(char);

/*-- Constructor/Destructor --------------*/
	QuizType();
	~QuizType();

private:
/*-- Instance ----------------------------*/
	string typeName;
	int openContext2;
	int numberOfAnswer;
	char answerType;
};

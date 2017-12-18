#pragma once

#include "stdafx.h"

#include "CommandSetQuiz.h"
#include "QuizDatabase.h"
#include "QuizTypeList.h"
#include "Account.h"
#include "AccountList.h"

using namespace std;

class QuizManager {
public:
/*-- Constructor/Destructor --------------*/
	QuizManager();
	~QuizManager();

/*-- Method ------------------------------*/
	bool Run_quizManager(Account*);
	int validCommand(int a_command);
	void executeCommand(int a_command);

	void Solve();
	void Create_Type();
	void Create_Quiz();

private:
/*-- Instance ----------------------------*/
	Account* my_account;
	AccountList my_accountList;
	CommandSetQuiz* my_commandSet;
	Quiz* my_quiz;
	QuizDatabase my_quizDatabase;
	QuizType* my_quizType;
	QuizTypeList my_quizTypeList;
};

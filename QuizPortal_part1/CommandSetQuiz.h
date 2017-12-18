#pragma once

#include "stdafx.h"

#include "CommandSet.h"

using namespace std;

class CommandSetQuiz : public CommandSet {
public:
/*-- Getter/Setter -----------------------*/
	int Get_command(int an_input) override;
	void Set_command(int a_location, int new_command) override;
/*-- Constructor/Destructor --------------*/
	CommandSetQuiz();
	~CommandSetQuiz();

private:
/*-- Instance ----------------------------*/
	int inputToCommand[7] = { 0, 1, 2, 3, 4, 5, 6 };
	// { Exit, All_Types, All_Quizzes, Solve, Create_Type(@), Create_Quiz(@), Account}
	// '£À' Means "Admin Only"
};

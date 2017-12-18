#include "stdafx.h"

#include "CommandSetQuiz.h"

using namespace std;

/*-- Getter/Setter -----------------------*/
int CommandSetQuiz::Get_command(int an_input) {
	return this->inputToCommand[an_input];
}
void CommandSetQuiz::Set_command(int a_location, int new_command) {
	inputToCommand[a_location] = new_command;
}

/*-- Constructor/Destructor --------------*/
CommandSetQuiz::CommandSetQuiz() {}
CommandSetQuiz::~CommandSetQuiz() {}

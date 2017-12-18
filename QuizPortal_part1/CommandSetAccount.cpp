#include "stdafx.h"

#include "CommandSetAccount.h"

using namespace std;

/*-- Getter/Setter -----------------------*/
int CommandSetAccount::Get_command(int an_input) {
	return this->inputToCommand[an_input];
}
void CommandSetAccount::Set_command(int a_location, int new_command) {
	inputToCommand[a_location] = new_command;
}

/*-- Constructor/Destructor --------------*/
CommandSetAccount::CommandSetAccount() {}
CommandSetAccount::~CommandSetAccount() {}

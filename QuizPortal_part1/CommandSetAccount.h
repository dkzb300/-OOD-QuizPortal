#pragma once

#include "stdafx.h"

#include "CommandSet.h"

using namespace std;

class CommandSetAccount : public CommandSet {
public:
/*-- Getter/Setter -----------------------*/
	int Get_command(int an_input) override;
	void Set_command(int a_location, int new_command) override;
/*-- Constructor/Destructor --------------*/
	CommandSetAccount();
	~CommandSetAccount();

private:
/*-- Instance ----------------------------*/
	int inputToCommand[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	// { Exit, Join, Restoration, Log_In, Log_Out, Quiz, My_Account, All_Account(£À)}
	// '£À' Means "Admin Only"
};

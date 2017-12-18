#pragma once

#include "stdafx.h"

#include "Account.h"
#include "AccountList.h"
#include "CommandSetAccount.h"

using namespace std;

class AccountManager {
public:
/*-- Getter/Setter -----------------------*/
	Account* Get_Account();

/*-- Constructor/Destructor --------------*/
	AccountManager();
	~AccountManager();

/*-- Method ------------------------------*/
	bool Run_accountManager(Account* an_account);
	int validCommand(int a_command);
	void executeCommand(int a_command);

	void createAccount();
	void loginAccount();
	void logoutAccount();
	void restoreAccount();

private:
/*-- Instance ----------------------------*/
	Account* my_account;
	AccountList my_accountList;
	CommandSetAccount* my_commandSet;
};

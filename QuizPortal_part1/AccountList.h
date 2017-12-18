#pragma once

#include "stdafx.h"

#include "Account.h"

using namespace std;

class AccountList {
public:
/*-- Getter/Setter -----------------------*/
	int Get_size();
	int Get_accountLocation();
	Account* Get_withoutLocation_Account();
	Account* Get_Location_Account(int a_location);

/*-- Constructor/Destructor --------------*/
	AccountList();
	~AccountList();

/*-- Method ------------------------------*/
	bool idIsExist(string new_accountID);
	void add(Account* an_Account);
	bool loginIsValid(string new_accountPW);
	bool keyIsExist(int new_uniqueKey);
	void load_database();
	void store_database();
	void Print_list(Account* given_Account);
	void refreshRank();

private:
/*-- Instance ----------------------------*/
	Account* list_Account[100] = {};
	int size = 0;
	int accountLocation = 0;
};

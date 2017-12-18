#pragma once

#include "stdafx.h"

using namespace std;

class Account {
public:
/*-- Getter/Setter -----------------------*/
	string Get_accountID();
	string Get_accountPW();
	int Get_uniqueKey();
	int Get_point();
	int Get_rank();

	void Set_accountID(string new_accountID);
	void Set_accountPW(string new_accountPW);
	void Set_uniqueKey(int inputInt);
	void Set_point(int new_point);
	void Set_rank(int new_rank);

/*-- Constructor/Destructor --------------*/
	Account();
	~Account();

/*-- Method ------------------------------*/
	string validID();
	bool characterIsValid(char a_char);
	string validPW();
	void Print_account();

private:
/*-- Instance ----------------------------*/
	string accountID;
	string accountPW;
	int uniqueKey;
	int point;
	int rank;
};

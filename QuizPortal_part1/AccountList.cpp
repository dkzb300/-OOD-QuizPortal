#include "stdafx.h"

#include "AccountList.h"

using namespace std;

/*-- Getter/Setter -----------------------*/
int AccountList::Get_size() {
	return this->size;
}
int AccountList::Get_accountLocation() {
	return this->accountLocation;
}
Account* AccountList::Get_withoutLocation_Account() {
	return this->Get_Location_Account(accountLocation);
}
Account* AccountList::Get_Location_Account(int a_location) {
	return this->list_Account[a_location];
}

/*-- Constructor/Destructor --------------*/
AccountList::AccountList() {
	size = 0;
	load_database();
}
AccountList::~AccountList() {}

/*-- Method ------------------------------*/
bool AccountList::idIsExist(string new_accountID) {
	Account* an_Account;
	string an_accountID;
	char left, right;
	bool same = false;


	for (int i = 0; i < Get_size(); i++) {
		an_Account = list_Account[i];
		an_accountID = an_Account->Get_accountID();
		if (new_accountID.size() == an_accountID.size()) {
			same = true;
			for (int j = 0; j < an_accountID.size(); j++) {
				if (new_accountID.size() == an_accountID.size()) {
					left = new_accountID.at(j);
					right = an_accountID.at(j);
					if (left != right) {
						if ((char)toupper(left) != right && (char)tolower(left) != right) {
							same = false;
							break;
						}
					}
				}
			}
		}
		if (same) {
			accountLocation = i;
			return same;
		}
	}

	return same;
}
void AccountList::add(Account* an_Account) {
	list_Account[size++] = an_Account;
}
bool AccountList::loginIsValid(string new_accountPW) {
	Account* an_Account;
	string an_accountPW;
	char left, right;
	bool same = false;

	an_Account = list_Account[accountLocation];
	an_accountPW = an_Account->Get_accountPW();
	
	if (new_accountPW.size() == an_accountPW.size()) {
		same = true;
		for (int i = 0; i < an_accountPW.size(); i++) {
			left = new_accountPW.at(i);
			right = an_accountPW.at(i);
			if (left != right) {
				if ((char)toupper(left) != right && (char)tolower(left) != right) {
					same = false;
					break;
				}
			}
		}
	}

	return same;
}
bool AccountList::keyIsExist(int new_uniqueKey) {
	Account *an_Account;
	int an_uniqueKey;

	for (int i = 0; i < Get_size(); i++) {
		an_Account = list_Account[i];
		an_uniqueKey = an_Account->Get_uniqueKey();

		if (new_uniqueKey == an_uniqueKey) {
			accountLocation = i;
			return true;
		}
	}
	
	return false;
}
void AccountList::load_database() {
	ifstream fin;
	char input[20];
	int a_number;
	fin.open("user_database.txt", ios::in);
	for (int i = 0; !fin.eof(); i++) {
		Account* an_account = new Account();
		fin >> input;
		an_account->Set_accountID(input);
		fin >> input;
		an_account->Set_accountPW(input);
		fin >> a_number;
		an_account->Set_uniqueKey(a_number);
		fin >> a_number;
		an_account->Set_point(a_number);
		fin >> a_number;
		an_account->Set_rank(a_number);
		*(list_Account + i) = (an_account);
		size = i;
	}
	list_Account[size] = NULL;
}
void AccountList::store_database() {
	Account* an_account;
	ofstream fout;
	fout.open("user_database.txt");
	for (int i = 0; i < this->Get_size(); i++) {
		an_account = this->Get_Location_Account(i);
		fout << an_account->Get_accountID() << endl;
		fout << an_account->Get_accountPW() << endl;
		fout << an_account->Get_uniqueKey() << endl;
		fout << an_account->Get_point() << endl;
		fout << an_account->Get_rank() << endl;
		fout << endl;
	}
	fout.close();
}
void AccountList::Print_list(Account* given_Account) {
	Account* an_account;
	cout << endl;
	cout << "# 현재 가입된 계정은 " << this->Get_size() << " 개 입니다." << endl;

	for (int i = 0; i < this->Get_size(); i++) {
		cout << endl;
		printf("# Account [ %2d ]", i + 1);

		an_account = this->Get_Location_Account(i);
		if (an_account->Get_uniqueKey() == given_Account->Get_uniqueKey())
			cout << " <- 본인";
		cout << endl;

		an_account->Print_account();
	}
}
void AccountList::refreshRank() {
	Account* left_account;
	Account* right_account;
	int aRank;

	for (int i = 0; i < this->Get_size(); i++) {
		left_account = this->Get_Location_Account(i);
		if (left_account->Get_point() > 0) {
			aRank = 1;
			for (int j = 0; j < this->Get_size(); j++) {
				right_account = this->Get_Location_Account(j);
				if (left_account->Get_point() < right_account->Get_point())
					aRank++;
			}
			this->Get_Location_Account(i)->Set_rank(aRank);
		}
	}
}

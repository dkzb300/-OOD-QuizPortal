#include "stdafx.h"

#include "Account.h"

using namespace std;

/*-- Constructor/Destructor --------------*/
Account::Account() {
	point = 0;
	rank = 0;
}
Account::~Account() {}

/*-- Getter/Setter -----------------------*/
string Account::Get_accountID() {
	return this->accountID;
}
string Account::Get_accountPW() {
	return this->accountPW;
}
int Account::Get_uniqueKey() {
	return this->uniqueKey;
}
int Account::Get_point() {
	return this->point;
}
int Account::Get_rank() {
	return this->rank;
}

void Account::Set_accountID(string new_accountID) {
	this->accountID = new_accountID;
}
void Account::Set_accountPW(string new_accountPW) {
	this->accountPW = new_accountPW;
}
void Account::Set_uniqueKey(int inputInt) {
	uniqueKey = inputInt;
}
void Account::Set_point(int new_point) {
	this->point = new_point;
}
void Account::Set_rank(int new_rank) {
	this->rank = new_rank;
}

/*-- Method ------------------------------*/
string Account::validID() {
	int length;
	string inputString;
	bool validation;
	cout << "▼ ID 를 입력해주세요.(5자 이상, 10자 이하)" << endl;

	while (true) {
		cout << "▲ 입력: ";
		cin >> inputString;

		length = inputString.size();

		if (length < 5 || length > 10)
			cout << "※ 다시 입력해주세요. (오류: 허용 외의 크기)" << endl;


		else {
			validation = true;

			for (int i = 0; i < length; i++) {
				if (!characterIsValid(inputString.at(i))) {
					cout << "※ 다시 입력해주세요. (오류: 특수문자)" << endl;
					validation = false;
					break;
				}
			}

			if(validation)
				return inputString;;
		}
	}
}
string Account::validPW() {
	int length;
	string inputString;
	bool validation;
	cout << "▼ PW 를 입력해주세요.(5자 이상, 10자 이하)" << endl;

	while (true) {
		cout << "▲ 입력: ";
		cin >> inputString;

		length = inputString.size();

		if (length < 5 || length > 10)
			cout << "※ 다시 입력해주세요. (오류: 허용 외의 크기)" << endl;


		else {
			validation = true;

			for (int i = 0; i < length; i++) {
				if (!characterIsValid(inputString.at(i))) {
					cout << "※ 다시 입력해주세요. (오류: 특수문자)" << endl;
					validation = false;
					break;
				}
			}

			if (validation)
				return inputString;;
		}
	}
}
bool Account::characterIsValid(char a_char) {
	int charToASCII = (int)a_char;
	if (charToASCII >= 48 && charToASCII <= 57)
		return true;
	else if (charToASCII >= 65 && charToASCII <= 90)
		return true;
	else if (charToASCII >= 97 && charToASCII <= 122)
		return true;
	else
		return false;
}
void Account::Print_account() {
	cout << "├ ID    : " << this->Get_accountID() << endl;
	cout << "├ PW    : " << this->Get_accountPW() << endl;
	cout << "├ Key   : " << this->Get_uniqueKey() << endl;

	if (this->Get_uniqueKey() / 1000 == 2) {
		cout << "├ 신원  : 관리자" << endl;
		cout << "├ point : 정보 없음" << endl;
	}
	else {
		cout << "├ 신원  : 일반" << endl;
		cout << "├ point : " << this->Get_point() << " 점" << endl;
	}
	
	if (this->Get_rank() >= INT_MAX)
		cout << "└ rank  : 정보 없음" << endl;
	else
		cout << "└ rank  : " << this->Get_rank() << " 위" << endl;

	return;
}

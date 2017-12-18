#include "stdafx.h"

#include "AccountManager.h"

using namespace std;

/*-- Getter/Setter -----------------------*/
Account* AccountManager::Get_Account() {
	return this->my_account;
}

/*-- Constructor/Destructor --------------*/
AccountManager::AccountManager() {
	my_commandSet = new CommandSetAccount();
}
AccountManager::~AccountManager() {}

/*-- Method ------------------------------*/
bool AccountManager::Run_accountManager(Account* an_account) {
	my_account = an_account;
	int commandInt = 0;
	int maxCommand;

	if (my_account != NULL) {
		my_accountList.load_database();
		my_accountList.refreshRank();

		my_accountList.keyIsExist(my_account->Get_uniqueKey());
		my_account->Set_rank(my_accountList.Get_withoutLocation_Account()->Get_rank());
	}

	while (true) {
		maxCommand = 0;
		cout << "▼ 명령:" << endl;
		cout << "[ Exit           ] : " << maxCommand++ << endl;
		if (my_account == NULL) {
			my_commandSet->Set_command(maxCommand, 1);
			cout << "[ Create         ] : " << maxCommand++ << endl;
			my_commandSet->Set_command(maxCommand, 2);
			cout << "[ Restoration    ] : " << maxCommand++ << endl;
			my_commandSet->Set_command(maxCommand, 3);
			cout << "[ Log_In         ] : " << maxCommand++ << endl;
		}
		else {
			my_commandSet->Set_command(maxCommand, 4);
			cout << "[ Log_Out        ] : " << maxCommand++ << endl;
			my_commandSet->Set_command(maxCommand, 5);
			cout << "[ Quiz           ] : " << maxCommand++ << endl;
			my_commandSet->Set_command(maxCommand, 6);
			cout << "[ My_Account     ] : " << maxCommand++ << endl;
			if (my_account->Get_uniqueKey() / 1000 == 2) {
				my_commandSet->Set_command(maxCommand, 7);
				cout << "[ All_Account(@) ] : " << maxCommand++ << endl;
			}
		}

		commandInt = validCommand(maxCommand);

		if (commandInt == 0) {
			my_accountList.store_database();
			return false;
		}
		else if (commandInt == 5) {
			my_accountList.store_database();
			return true;
		}
		else {
			executeCommand(commandInt);
			cout << endl;
		}
	}
}
int AccountManager::validCommand(int a_maxCommand) {
	int input;
	while (true) {
		cout << "▲ 입력: ";
		cin >> input;

		if (input >= 0 && input < a_maxCommand)
			return my_commandSet->Get_command(input);
		else
			cout << "※ 다시 입력해주세요. (오류: 존재하지 않는 명령)" << endl;
	}
}
void AccountManager::executeCommand(int a_command) {
	switch (a_command)
	{
	case 1:
		createAccount();
		return;
	case 2:
		restoreAccount();
		return;
	case 3:
		loginAccount();
		return;
	case 4:
		logoutAccount();
		return;
	case 6:
		cout << endl;
		cout << "# 회원님의 계정 정보는 다음과 같습니다." << endl;
		my_account->Print_account();
		return;
	case 7:
		my_accountList.Print_list(my_account);
		return;
	default:
		return;
	}
}

void AccountManager::createAccount() {
	int inputInt;
	string new_accountID;
	string new_accountPW;

	srand((unsigned)time(NULL));
	
	cout << endl;
	cout << "＃ 새로운 계정을 작성합니다." << endl;
	cout << endl;
	cout << "▼ 계정 종류:" << endl;
	cout << "[ Normal ] : 1" << endl;
	cout << "[ Admin  ] : 2" << endl;

	while (true) {
		cout << "▲ 입력: ";
		cin >> inputInt;

		if (inputInt != 1 && inputInt != 2)
			cout << "※ 다시 입력해주세요." << endl;
		else
			break;
	}

	my_account = new Account();

	while (true) {
		new_accountID = my_account->validID();
		if (my_accountList.idIsExist(new_accountID)) {
			cout << "※ 다시 입력해주세요. (오류: 이미 존재하는 ID)" << endl;
		}
		else break;
	}

	new_accountPW = my_account->validPW();
	
	my_account->Set_accountID(new_accountID);
	my_account->Set_accountPW(new_accountPW);
	inputInt = (inputInt * 1000) + (rand() % 1000);
	my_account->Set_uniqueKey(inputInt);
	my_account->Set_point(0);
	my_account->Set_rank(INT_MAX);

	my_accountList.add(my_account);
	
	cout << endl;
	cout << "＃ 회원 가입이 완료되었습니다." << endl;
	cout << "＃ 회원 님의 비밀번호 복구 키는 " << my_account->Get_uniqueKey() << " 입니다." << endl;

	my_account = NULL;
}
void AccountManager::logoutAccount() {
	my_account = NULL;
	cout << endl;
	cout << "＃ 로그아웃 했습니다." << endl;
}
void AccountManager::loginAccount() {
	Account* an_account;
	string new_accountID;
	string new_accountPW;

	my_account = new Account();

	while (true) {
		new_accountID = my_account->validID();
		if (! my_accountList.idIsExist(new_accountID)) {
			cout << "※ 다시 입력해주세요. (오류: 존재하지 않는 ID)" << endl;
		}
		else break;
	}

	while (true) {
		new_accountPW = my_account->validPW();
		if (!my_accountList.loginIsValid(new_accountPW)) {
			cout << "※ 다시 입력해주세요. (오류: PW 불일치)" << endl;
		}
		else break;
	}

	my_account->Set_accountID(new_accountID);
	my_account->Set_accountPW(new_accountPW);

	an_account = my_accountList.Get_withoutLocation_Account();
	my_account->Set_uniqueKey(an_account->Get_uniqueKey());
	my_account->Set_point(an_account->Get_point());
	my_account->Set_rank(an_account->Get_rank());

	cout << endl;
	cout << "＃ 로그인이 완료되었습니다." << endl;
	
}
void AccountManager::restoreAccount() {
	int new_uniqueKey;
	string an_accountID;
	string an_accountPW;

	cout << "▼ 복구 키를 입력해주세요. (4자리 숫자, 맨 앞 자리는 1 또는 2)" << endl;

	my_account = new Account();

	while (true) {
		cout << "▲ 입력: ";
		cin >> new_uniqueKey;
		if (new_uniqueKey < 1000 || new_uniqueKey > 2999)
			cout << "※ 다시 입력해주세요. (오류: 허용 외의 크기)" << endl;
		else if(! my_accountList.keyIsExist(new_uniqueKey)) {
			cout << "※ 다시 입력해주세요. (오류: 존재하지 않는 복구 키)" << endl;
		}
		else break;
	}

	an_accountID = my_accountList.Get_withoutLocation_Account()->Get_accountID();
	an_accountPW = my_accountList.Get_withoutLocation_Account()->Get_accountPW();

	cout << endl;
	cout << "＃ 회원님의 ID는 " << an_accountID << " 입니다." << endl;
	cout << "＃ 회원님의 PW는 " << an_accountPW << " 입니다." << endl;

	my_account = NULL;
}

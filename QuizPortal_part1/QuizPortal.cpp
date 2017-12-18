// QuizPortal.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"

#include "IncludesForMain.h"

using namespace std;

int main() {
	Account* my_account = NULL;
	AccountManager* my_accountManager = new AccountManager();
	QuizManager* my_quizManager = new QuizManager();
	bool transferToOtherManager;
	bool accountIsAdmin;

	cout << "<< Quiz Portal �� �����մϴ�. >>" << endl;
	cout << endl;

	while (true) {
		while (true) {
			transferToOtherManager = my_accountManager->Run_accountManager(my_account);
			if (transferToOtherManager)
				break;
			else {
				cout << endl;
				cout << "<< Quiz Portal �� �����մϴ�. >>" << endl;
				return 0;
			}
		}

		my_account = my_accountManager->Get_Account();

		while (true) {
			transferToOtherManager = my_quizManager->Run_quizManager(my_account);
			if (transferToOtherManager)
				break;
			else {
				cout << endl;
				cout << "<< Quiz Portal �� �����մϴ�. >>" << endl;
				return 0;
			}
		}
	}

    return 0;
}

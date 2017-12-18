// QuizPortal.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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

	cout << "<< Quiz Portal 을 시작합니다. >>" << endl;
	cout << endl;

	while (true) {
		while (true) {
			transferToOtherManager = my_accountManager->Run_accountManager(my_account);
			if (transferToOtherManager)
				break;
			else {
				cout << endl;
				cout << "<< Quiz Portal 을 종료합니다. >>" << endl;
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
				cout << "<< Quiz Portal 을 종료합니다. >>" << endl;
				return 0;
			}
		}
	}

    return 0;
}

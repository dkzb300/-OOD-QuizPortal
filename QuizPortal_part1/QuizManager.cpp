#include "stdafx.h"

#include "QuizManager.h"

using namespace std;

/*-- Constructor/Destructor --------------*/
QuizManager::QuizManager() {
	my_commandSet = new CommandSetQuiz();
}
QuizManager::~QuizManager() {}

/*-- Method ------------------------------*/
bool QuizManager::Run_quizManager(Account* an_account) {
	my_account = an_account;
	int commandInt = 0;
	int maxCommand;

	my_accountList.load_database();

	bool accountIsAdmin = my_account->Get_uniqueKey() / 1000 == 2 ? true : false;

	
	if (my_quizDatabase.Get_size() <= 0 && ! accountIsAdmin) {
		cout << "�� ���� ������ ��� ���� ������ �� �����ϴ�." << endl;
		return true;
	}

	my_accountList.keyIsExist(my_account->Get_uniqueKey());

	while (true) {
		maxCommand = 0;
		cout << "�� ���:" << endl;
		cout << "[ Exit           ] : " << maxCommand++ << endl;

		if (my_quizTypeList.Get_size() > 0) {
			my_commandSet->Set_command(maxCommand, 1);
			cout << "[ All_Types      ] : " << maxCommand++ << endl;
		}

		if (my_quizDatabase.Get_size() > 0) {
			my_commandSet->Set_command(maxCommand, 2);
			cout << "[ All_Quizzes    ] : " << maxCommand++ << endl;
		}

		if (!accountIsAdmin) {
			my_commandSet->Set_command(maxCommand, 3);
			cout << "[ Solve          ] : " << maxCommand++ << endl;
		}

		if (accountIsAdmin) {
			my_commandSet->Set_command(maxCommand, 4);
			cout << "[ Create_Type(@) ] : " << maxCommand++ << endl;
			my_commandSet->Set_command(maxCommand, 5);
			cout << "[ Create_Quiz(@) ] : " << maxCommand++ << endl;
		}

		my_commandSet->Set_command(maxCommand, 6);
		cout << "[ Account        ] : " << maxCommand++ << endl;

		commandInt = validCommand(maxCommand);


		
		if (commandInt == 0) {
			my_quizTypeList.store_Database();
			my_quizDatabase.store_Database();
			my_accountList.store_database();
			return false;
		}
		else if (commandInt == 6) {
			my_quizTypeList.store_Database();
			my_quizDatabase.store_Database();
			my_accountList.store_database();
			return true;
		}
		else {
			executeCommand(commandInt);
			cout << endl;
		}

		my_accountList.Get_withoutLocation_Account()->Set_point(my_account->Get_point());

		my_accountList.refreshRank();
		
	}

	return false;
}
int QuizManager::validCommand(int a_maxCommand) {
	int input;
	while (true) {
		cout << "�� �Է�: ";
		cin >> input;

		if (input >= 0 && input < a_maxCommand)
			return my_commandSet->Get_command(input);
		else
			cout << "�� �ٽ� �Է����ּ���. (����: �������� �ʴ� ���)" << endl;
	}
}
void QuizManager::executeCommand(int a_command) {
	switch (a_command)
	{
	case 1:
		my_quizTypeList.Print_list();
		return;
	case 2:
		this->my_quizDatabase.Print_Database();
		return;
	case 3:
		this->Solve();
		return;
	case 4:
		this->Create_Type();
		return;
	case 5:
		this->Create_Quiz();
		return;
	default:
		return;
	}
}

void QuizManager::Solve() {
	Account* an_account = my_account;

	int my_type;
	int my_difficulty;
	int my_point;

	string my_typeName;
	int my_openContext2;
	int my_numberOfAnswer;
	char my_answerType;

	int a_number;
	float a_float;
	char a_char;
	char an_char[100];
	string input;

	bool failOnce = false;

	cout << endl;
	cout << "# ���� Ǯ�̸� �����մϴ�." << endl;

	cout << "�� ��� �������ּ���. (���� ��ȣ�� ������ �Է�)" << endl;
	while (true) {
		cout << "�� �Է�: ";
		cin >> a_number;
		if (a_number <= 0)
			cout << "�� �ٽ� �Է����ּ���. (����: 0�� ���ϴ� ������� ����.)" << endl;
		else if (a_number > my_quizDatabase.Get_size())
			cout << "�� �ٽ� �Է����ּ���. (����: �������� �ʴ� ���� ��ȣ.)" << endl;
		else
			break;
	}

	my_quiz = my_quizDatabase.Get_Location_Quiz(a_number - 1);
	my_type = my_quiz->Get_typeNumber();
	my_difficulty = my_quiz->Get_Difficulty();
	my_point = my_quiz->Get_Point();

	my_quizType = my_quizTypeList.Get_Location_QuizType(my_type - 1);
	my_typeName = my_quizType->Get_typeName();
	my_openContext2 = my_quizType->Get_openContext2();
	my_numberOfAnswer = my_quizType->Get_numberOfAnswer();
	my_answerType = my_quizType->Get_answerType();

	cout << "# " << a_number << " �� ������ Ǯ�ڽ��ϴ�. ( " << my_typeName << ", ���̵�: " << my_difficulty;
	cout << ", ����: " << my_point << " )" << endl;

	cout << "# ����: " << endl;
	cout << my_quiz->Get_Context1() << endl;
	if (my_openContext2) {
		cout << "# ����:" << endl;
		cout << my_quiz->Get_Context2() << endl;
	}

	cout << "�� ������ �Է����ּ���." << endl;;

	while (true) {
		cout << "�� �Է�: ";
		cin.getline(an_char, 100);
		if(!failOnce)
			cin.getline(an_char, 100);
		if (my_quiz->Get_Answer().compare(an_char) != 0) {
			if (!failOnce) {
				cout << "�� �����Դϴ�. (�� ���� ��ȸ�� �ֽ��ϴ�.)" << endl;
				if (!my_openContext2) {
					cout << "# ��Ʈ:" << endl;
					cout << my_quiz->Get_Context2() << endl;
				}
				failOnce = true;
			}
			else {
				cout << "�� �����Դϴ�. (��ȸ�� ��� �����Ͽ����ϴ�.)" << endl;
				break;
			}
		}
		else {
			cout << "# �����Դϴ�." << endl;
			failOnce = false;
			break;
		}
	}

	if(! failOnce)
		my_account->Set_point(an_account->Get_point() + my_quiz->Get_Point());
	return;
}
void QuizManager::Create_Type() {
	QuizType* a_quizType = new QuizType();
	int a_number;
	char a_char;
	string input;

	cout << endl;
	cout << "# ���ο� ���� ������ �ۼ��մϴ�." << endl;

	cout << "�� ���� ���� �̸��� �Է����ּ���." << endl;
	cout << "�� �Է�: ";
	cin >> input;
	a_quizType->Set_typeName(input);

	cout << "�� �� ��° ������ ��뿡 ���� �Է����ּ���." << endl;
	cout << "[ ���� Ǯ���� ��Ʈ (����� ����) ] : 0" << endl;
	cout << "[ ���� Ǯ���� ���� (��� ����)   ] : 1" << endl;
	cout << "�� �Է�: ";
	cin >> a_number;
	a_quizType->Set_openContext2(a_number);

	cout << "�� �Է��ؾ� �� ������ ������ �Է����ּ���." << endl;
	cout << "�� �Է�: ";
	cin >> a_number;
	a_quizType->Set_numberOfAnswer(a_number);

	cout << "�� �Է��ؾ� �� ������ �ڷ����� �Է����ּ���." << endl;
	cout << "[ Int   (������)       ] : 'i'" << endl;
	cout << "[ Float (�ε��Ҽ�����) ] : 'f'" << endl;
	cout << "[ Char  (������)       ] : 'c'" << endl;
	cout << "�� �Է�: ";
	cin >> a_char;
	a_quizType->Set_answerType(a_char);

	my_quizTypeList.add(a_quizType);
}
void QuizManager::Create_Quiz() {
	Quiz* a_Quiz = new Quiz();
	int a_number;
	char a_char;
	char an_char[1000];
	string input;

	cout << endl;
	cout << "# ���ο� ��� �ۼ��մϴ�." << endl;

	cout << "�� ���� ���� ���ڸ� �Է����ּ���." << endl;
	while (true) {
		cout << "�� �Է�: ";
		cin >> a_number;
		if (a_number <= 0)
			cout << "�� �ٽ� �Է����ּ���. (����: 0�� ���ϴ� ������� ����.)" << endl;
		else if (a_number > my_quizTypeList.Get_size())
			cout << "�� �ٽ� �Է����ּ���. (����: �������� �ʴ� ���� ��ȣ.)" << endl;
		else
			break;
	}
	a_Quiz->Set_typeNumber(a_number);

	cout << "�� ù ��° ���� (����) �� �Է����ּ���." << endl;
	cout << "�� �Է�: ";
	cin.getline(an_char, 1000);
	cin.getline(an_char, 1000);
	a_Quiz->Set_Context1(an_char);

	cout << "�� �� ��° ���� (���� �Ǵ� ��Ʈ) �� �Է����ּ���." << endl;
	cout << "�� �Է�: ";
	cin.getline(an_char, 1000);
	a_Quiz->Set_Context2(an_char);

	cout << "�� ������ ���� (������ ��� ����) �� �Է����ּ���. " << endl;
	cout << "�� �Է�: ";
	cin.getline(an_char, 1000);
	a_Quiz->Set_Answer(an_char);

	cout << "�� ������ ���� (����, 1 ~ 5) �� �Է����ּ���." << endl;
	cout << "�� �Է�: ";
	cin >> a_number;
	a_Quiz->Set_Point(a_number);

	cout << "�� ������ ���̵� (����, 1 ~ 5) �� �Է����ּ���." << endl;
	cout << "�� �Է�: ";
	cin >> a_number;
	a_Quiz->Set_Difficulty(a_number);

	my_quizDatabase.add(a_Quiz);
}

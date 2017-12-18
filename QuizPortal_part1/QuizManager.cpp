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
		cout << "※ 아직 생성된 퀴즈가 없어 접속할 수 없습니다." << endl;
		return true;
	}

	my_accountList.keyIsExist(my_account->Get_uniqueKey());

	while (true) {
		maxCommand = 0;
		cout << "▼ 명령:" << endl;
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
		cout << "▲ 입력: ";
		cin >> input;

		if (input >= 0 && input < a_maxCommand)
			return my_commandSet->Get_command(input);
		else
			cout << "※ 다시 입력해주세요. (오류: 존재하지 않는 명령)" << endl;
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
	cout << "# 퀴즈 풀이를 시작합니다." << endl;

	cout << "▼ 퀴즈를 선택해주세요. (퀴즈 번호를 정수로 입력)" << endl;
	while (true) {
		cout << "▲ 입력: ";
		cin >> a_number;
		if (a_number <= 0)
			cout << "※ 다시 입력해주세요. (오류: 0번 이하는 취급하지 않음.)" << endl;
		else if (a_number > my_quizDatabase.Get_size())
			cout << "※ 다시 입력해주세요. (오류: 존재하지 않는 퀴즈 번호.)" << endl;
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

	cout << "# " << a_number << " 번 문제를 풀겠습니다. ( " << my_typeName << ", 난이도: " << my_difficulty;
	cout << ", 점수: " << my_point << " )" << endl;

	cout << "# 본문: " << endl;
	cout << my_quiz->Get_Context1() << endl;
	if (my_openContext2) {
		cout << "# 조건:" << endl;
		cout << my_quiz->Get_Context2() << endl;
	}

	cout << "▼ 정답을 입력해주세요." << endl;;

	while (true) {
		cout << "▲ 입력: ";
		cin.getline(an_char, 100);
		if(!failOnce)
			cin.getline(an_char, 100);
		if (my_quiz->Get_Answer().compare(an_char) != 0) {
			if (!failOnce) {
				cout << "※ 오답입니다. (한 번의 기회가 있습니다.)" << endl;
				if (!my_openContext2) {
					cout << "# 힌트:" << endl;
					cout << my_quiz->Get_Context2() << endl;
				}
				failOnce = true;
			}
			else {
				cout << "※ 오답입니다. (기회를 모두 소진하였습니다.)" << endl;
				break;
			}
		}
		else {
			cout << "# 정답입니다." << endl;
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
	cout << "# 새로운 퀴즈 유형을 작성합니다." << endl;

	cout << "▼ 퀴즈 유형 이름을 입력해주세요." << endl;
	cout << "▲ 입력: ";
	cin >> input;
	a_quizType->Set_typeName(input);

	cout << "▼ 두 번째 문장의 사용에 대해 입력해주세요." << endl;
	cout << "[ 문제 풀이의 힌트 (오답시 공개) ] : 0" << endl;
	cout << "[ 문제 풀이의 조건 (즉시 공개)   ] : 1" << endl;
	cout << "▲ 입력: ";
	cin >> a_number;
	a_quizType->Set_openContext2(a_number);

	cout << "▼ 입력해야 할 정답의 갯수를 입력해주세요." << endl;
	cout << "▲ 입력: ";
	cin >> a_number;
	a_quizType->Set_numberOfAnswer(a_number);

	cout << "▼ 입력해야 할 정답의 자료형을 입력해주세요." << endl;
	cout << "[ Int   (정수형)       ] : 'i'" << endl;
	cout << "[ Float (부동소숫점형) ] : 'f'" << endl;
	cout << "[ Char  (문자형)       ] : 'c'" << endl;
	cout << "▲ 입력: ";
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
	cout << "# 새로운 퀴즈를 작성합니다." << endl;

	cout << "▼ 퀴즈 유형 숫자를 입력해주세요." << endl;
	while (true) {
		cout << "▲ 입력: ";
		cin >> a_number;
		if (a_number <= 0)
			cout << "※ 다시 입력해주세요. (오류: 0번 이하는 취급하지 않음.)" << endl;
		else if (a_number > my_quizTypeList.Get_size())
			cout << "※ 다시 입력해주세요. (오류: 존재하지 않는 유형 번호.)" << endl;
		else
			break;
	}
	a_Quiz->Set_typeNumber(a_number);

	cout << "▼ 첫 번째 문장 (본문) 을 입력해주세요." << endl;
	cout << "▲ 입력: ";
	cin.getline(an_char, 1000);
	cin.getline(an_char, 1000);
	a_Quiz->Set_Context1(an_char);

	cout << "▼ 두 번째 문장 (조건 또는 힌트) 을 입력해주세요." << endl;
	cout << "▲ 입력: ";
	cin.getline(an_char, 1000);
	a_Quiz->Set_Context2(an_char);

	cout << "▼ 퀴즈의 정답 (복수일 경우 띄어쓰기) 을 입력해주세요. " << endl;
	cout << "▲ 입력: ";
	cin.getline(an_char, 1000);
	a_Quiz->Set_Answer(an_char);

	cout << "▼ 퀴즈의 점수 (정수, 1 ~ 5) 를 입력해주세요." << endl;
	cout << "▲ 입력: ";
	cin >> a_number;
	a_Quiz->Set_Point(a_number);

	cout << "▼ 퀴즈의 난이도 (정수, 1 ~ 5) 를 입력해주세요." << endl;
	cout << "▲ 입력: ";
	cin >> a_number;
	a_Quiz->Set_Difficulty(a_number);

	my_quizDatabase.add(a_Quiz);
}

#include "stdafx.h"

#include "QuizTypeList.h"

using namespace std;

/*-- Getter/Setter -----------------------*/
int QuizTypeList::Get_size() {
	return this->size;
}
int QuizTypeList::Get_quizTypeLocation() {
	return this->quizTypeLocation;
}
QuizType* QuizTypeList::Get_withoutLocation_Account() {
	return this->Get_Location_QuizType(quizTypeLocation);
}
QuizType* QuizTypeList::Get_Location_QuizType(int a_location) {
	return this->list_QuizType[a_location];
}

/*-- Constructor/Destructor --------------*/
QuizTypeList::QuizTypeList() {
	this->load_Database();
}
QuizTypeList::~QuizTypeList() {}

/*-- Method ------------------------------*/
void QuizTypeList::add(QuizType* new_QuizType) {
	list_QuizType[size++] = new_QuizType;
}
void QuizTypeList::load_Database() {
	ifstream fin;
	char input[100];
	int a_number;
	char a_char;
	QuizType* a_quizType;

	
	fin.open("quiztype_list.txt", ios::in);
	for (int i = 0; !fin.eof(); i++) {
		a_quizType = new QuizType();
		fin.getline(input, 100);
		if (i > 0) {
			fin.getline(input, 100);
			fin.getline(input, 100);
		}
		a_quizType->Set_typeName(input);
		fin >> a_number;
		a_quizType->Set_openContext2(a_number);
		fin >> a_number;
		a_quizType->Set_numberOfAnswer(a_number);
		fin >> a_char;
		a_quizType->Set_answerType(a_char);
		*(list_QuizType + i) = (a_quizType);
		size = i;
	}
	 list_QuizType[size] = NULL;
	
}
void QuizTypeList::store_Database() {
	QuizType* a_quizType;
	ofstream fout;
	fout.open("quiztype_list.txt");
	for (int i = 0; i < this->Get_size(); i++) {
		a_quizType = this->Get_Location_QuizType(i);

		fout << a_quizType->Get_typeName() << endl;
		fout << a_quizType->Get_openContext2() << endl;
		fout << a_quizType->Get_numberOfAnswer() << endl;
		fout << a_quizType->Get_answerType() << endl;
		fout << endl;
	}
	fout.close();
}
void QuizTypeList::Print_list() {
	QuizType* a_Type;

	cout << endl;
	cout << "# 현재 생성된 문제는 " << this->Get_size() << " 개 입니다." << endl;

	for (int i = 0; i < this->Get_size(); i++) {
		a_Type = this->Get_Location_QuizType(i);

		cout << endl;
		printf("# QuizType [ %2d ]\n", i + 1);

		cout << "├ 유형 이름             : " << a_Type->Get_typeName() << endl;
		cout << "├ 힌트 대신 조건을 출력 : " << a_Type->Get_openContext2() << endl;
		cout << "├ 입력할 답의 갯수      : " << a_Type->Get_numberOfAnswer() << endl;
		cout << "└ 입력할 답의 자료형    : " << a_Type->Get_answerType() << endl;
	}
}

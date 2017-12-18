#include "stdafx.h"

#include "QuizDatabase.h"

using namespace std;

/*-- Getter/Setter -----------------------*/
int QuizDatabase::Get_size() {
	return this->size;
}
int QuizDatabase::Get_quizLocation() {
	return this->quizLocation;
}
Quiz* QuizDatabase::Get_withoutLocation_Quiz() {
	return this->Get_Location_Quiz(quizLocation);
}
Quiz* QuizDatabase::Get_Location_Quiz(int a_location) {
	return this->quizDatabase[a_location];
}

/*-- Constructor/Destructor --------------*/
QuizDatabase::QuizDatabase() {
	this->load_Database();
}
QuizDatabase::~QuizDatabase() {}

/*-- Method ------------------------------*/
void QuizDatabase::Print_Database() {
	Quiz* a_Quiz;

	cout << endl;
	cout << "# 현재 생성된 문제는 " << this->Get_size() << " 개 입니다." << endl;

	for (int i = 0; i < this->Get_size(); i++) {
		a_Quiz = this->Get_Location_Quiz(i);

		cout << endl;
		printf("# Quiz [ %2d ]\n", i + 1);

		cout << "├ 유형번호  : " << a_Quiz->Get_typeNumber() << endl;
		cout << "├ 점수      : " << a_Quiz->Get_Point() << endl;
		cout << "└ 난이도    : " << a_Quiz->Get_Difficulty() << endl;
	}
}
void QuizDatabase::add(Quiz* new_Quiz) {
	this->quizDatabase[size++] = new_Quiz;
}
void QuizDatabase::load_Database() {
	char input[100];
	int a_number;

	Quiz* a_Quiz;


	fin.open("quiz_database.txt", ios::in);
	for (int i = 0; !fin.eof(); i++) {
		a_Quiz = new Quiz();

		fin >> a_number;
		a_Quiz->Set_typeNumber(a_number);
		fin.getline(input, 100);
		fin.getline(input, 100);
		a_Quiz->Set_Context1(input);
		fin.getline(input, 100);
		a_Quiz->Set_Context2(input);
		fin.getline(input, 100);
		a_Quiz->Set_Answer(input);
		fin >> a_number;
		a_Quiz->Set_Point(a_number);
		fin >> a_number;
		a_Quiz->Set_Difficulty(a_number);
		*(quizDatabase + i) = (a_Quiz);
		size = i;
	}
	quizDatabase[size] = NULL;
}
void QuizDatabase::store_Database() {
	Quiz* a_Quiz;
	ofstream fout;
	fout.open("quiz_database.txt");
	for (int i = 0; i < this->Get_size(); i++) {
		a_Quiz = this->Get_Location_Quiz(i);

		fout << a_Quiz->Get_typeNumber() << endl;
		fout << a_Quiz->Get_Context1() << endl;
		fout << a_Quiz->Get_Context2() << endl;
		fout << a_Quiz->Get_Answer() << endl;
		fout << a_Quiz->Get_Point() << endl;
		fout << a_Quiz->Get_Difficulty() << endl;
		fout << endl;
	}
	fout.close();
}

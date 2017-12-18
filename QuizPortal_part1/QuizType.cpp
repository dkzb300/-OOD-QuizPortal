#include "stdafx.h"

#include "QuizType.h"

using namespace std;

/*-- Getter/Setter -----------------------*/
string QuizType::Get_typeName() {
	return this->typeName;
}
int QuizType::Get_openContext2() {
	return this->openContext2;
}
int QuizType::Get_numberOfAnswer() {
	return this->numberOfAnswer;
}
char QuizType::Get_answerType() {
	return this->answerType;
}

void QuizType::Set_typeName(string new_typeName) {
	this->typeName = new_typeName;
}
void QuizType::Set_openContext2(int new_openContext2) {
	this->openContext2 = new_openContext2;
}
void QuizType::Set_numberOfAnswer(int new_numberOfAnswer) {
	this->numberOfAnswer = new_numberOfAnswer;
}
void QuizType::Set_answerType(char new_answerType) {
	this->answerType = new_answerType;
}

/*-- Constructor/Destructor --------------*/
QuizType::QuizType() {}
QuizType::~QuizType() {}

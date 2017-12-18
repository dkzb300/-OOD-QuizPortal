#include "stdafx.h"
#include "Quiz.h"

/*-- Getter/Setter -----------------------*/
int Quiz::Get_Point() {
	return this->point;
}
int Quiz::Get_Difficulty() {
	return this->difficulty;
}
string Quiz::Get_Context1() {
	return this->context1;
}
string Quiz::Get_Context2() {
	return this->context2;
}
int Quiz::Get_typeNumber() {
	return this->typeNumber;
}
string Quiz::Get_Answer() {
	return this->answer;
}

void Quiz::Set_Point(int given_Point) {
	this->point = given_Point;
}
void Quiz::Set_Difficulty(int given_Difficulty) {
	this->difficulty = given_Difficulty;
}
void Quiz::Set_Context1(string given_Context1) {
	this->context1 = given_Context1;
}
void Quiz::Set_Context2(string given_Context2) {
	this->context2 = given_Context2;
}
void Quiz::Set_typeNumber(int given_TypeNumber) {
	this->typeNumber = given_TypeNumber;
}
void Quiz::Set_Answer(string given_Answer) {
	this->answer = given_Answer;
}

/*-- Constructor/Destructor --------------*/
Quiz::Quiz() {}
Quiz::~Quiz() {}
Quiz::Quiz(int given_Point, int given_Difficulty) {
	point = given_Point;
	difficulty = given_Difficulty;
}

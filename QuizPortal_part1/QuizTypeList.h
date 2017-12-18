#pragma once

#include "stdafx.h"

#include "QuizType.h"

using namespace std;

class QuizTypeList {
public:
/*-- Getter/Setter -----------------------*/
	int Get_size();
	int Get_quizTypeLocation();
	QuizType* Get_withoutLocation_Account();
	QuizType* Get_Location_QuizType(int a_location);

/*-- Constructor/Destructor --------------*/
	QuizTypeList();
	~QuizTypeList();

/*-- Method ------------------------------*/
	void load_Database();
	void store_Database();
	void add(QuizType* new_QuizType);
	void Print_list();

private:
/*-- Instance ----------------------------*/
	QuizType* list_QuizType[100] = {};
	int size = 0;
	int quizTypeLocation = 0;
	ifstream fin;
	ofstream fout;
};
#pragma once

#include "stdafx.h"
#include "Quiz.h"

class QuizDatabase {
public:
/*-- Getter/Setter -----------------------*/
	int Get_size();
	int Get_quizLocation();
	Quiz* Get_withoutLocation_Quiz();
	Quiz* Get_Location_Quiz(int a_location);

/*-- Constructor/Destructor --------------*/
	QuizDatabase();
	~QuizDatabase();

/*-- Method ------------------------------*/
	void load_Database();
	void store_Database();
	void add(Quiz* new_Quiz);
	void Print_Database();

private:
/*-- Instance ----------------------------*/
	Quiz* quizDatabase[100] = {};
	int size = 0;
	int quizLocation = 0;
	ifstream fin;
	ofstream fout;
};

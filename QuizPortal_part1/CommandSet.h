#pragma once

#include "stdafx.h"

using namespace std;

class CommandSet {
protected:
/*-- Getter/Setter -----------------------*/
	virtual int Get_command(int an_input) = 0;
	virtual void Set_command(int a_location, int new_command) = 0;
};

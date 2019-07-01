#pragma once
#include "Input.h"


#define DEBUG_ITEMS 3

class DebugList
{
public:
	DebugList();
	~DebugList();
	void Update();


	//ITEM 0 == key 1 BOXES
	//ITEM 2 == key 2 LINES
	//ITEM 3 == key 3 DESTINATION
	bool item[DEBUG_ITEMS];
	
};
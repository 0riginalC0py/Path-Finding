#pragma once
#include "Input.h"


#define DEBUG_ITEMS 5

class DebugList
{
public:
	DebugList();
	~DebugList();
	void Update();

	//ITEM 0 == key 1 PATH
	//ITEM 1 == key 2 START AND END POINT
	//ITEM 2 == key 3 NODE CONNECTIONS
	//ITEM 4 == key 3 then 4 FSCORE (TOP LEFT OF SQUARE)
	
	bool item[DEBUG_ITEMS];
};
#pragma once
#include "BB.h"
#include "Player.h"

class Level
{
public:
	Level();
	~Level();




private:
	
	BB m_levelManager;
	Player* m_player;

};


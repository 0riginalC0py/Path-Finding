#pragma once
#include "Grid.h"
#include <vector>
#include "Vector2.h"
#include "DebugList.h"


//Variables for Player.cpp
#define PLAYER_START_POSX 600.0f
#define PLAYER_START_POSY 400.0f
#define PLAYER_SPEED 100.0f

//Variables set in Game2D.cpp
#define GRID_WIDTH 100
#define GRID_HEIGHT 100

//Variables for Grid.cpp
#define SQUARE_SIZE 30.0F
#define SQUARE_GAP_BETWEEN 2.5f
#define GRID_OFFSET_POSX 0
#define GRID_OFSSET_POSY 0

//Variables for Costs Between nodes
//In Grid.cpp


#define DIAGNOL_UP_LEFT 14.0f
#define DIAGNOL_UP_RIGHT 14.0f
#define DIAGNOL_DOWN_LEFT 14.0f
#define DIAGNOL_DOWN_RIGHT 14.0f

#define STRAIGHT_UP 10.0f
#define STRAIGHT_DOWN 10.0f
#define STRAIGHT_LEFT 10.0f
#define STRAIGHT_RIGHT 10.0f

//*****************************
//HEURISTIC CALCULATION DOES NOT
//WORK WITH INDIVIDUAL SETTINGS
//FOR 
//*****************************
#define STRAIGHTS 10.0f
#define DIAGNOLS 14.0f

//Variable for determining how
//accurate the heuristic is.
//Found in Grid.
#define INADMISSIBLE_HEUR 1.0f

//Only header.
class BB
{
public:
	BB(){}
	~BB(){}
	
	//Mouse Postion
	Vector2 v2MousePos;
	//Grid is created in Game2D constructor
	Grid* m_grid;
	//Last path inputed by player.
	std::vector<Vector2> m_globalPath;
	//Camera position to be used for adjustments on grid.
	Vector2 m_camera;

	DebugList m_debugList;
	//int m_totalSquares;
};


//After my initial idea
//
//


#pragma once

#include "Game.h"
#include "Renderer2D.h"
#include "Vector2.h"
#include "BB.h"


#define WINDOW_OFFSET_X 650
#define WINDOW_OFFSET_Y 350


class Player;

class Game2D : public aie::Game
{
public:
	Game2D(const char* title, int width, int height, bool fullscreen);
	virtual ~Game2D();

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
	aie::Renderer2D*	m_2dRenderer;

	// Example textures.
	aie::Font*			m_font;

	

	// Player.
	Player* m_Player;
	//Vector2 m_start;
	//Vector2 m_end;
	//Grid* m_Grid;
	BB m_levelManager;
	//std::vector<Vector2> m_globalPath;
};




//Need to put start and end into player class.
//Need to send camera positions to player class as well.
//


//In player class.
//at player init
// int m_CurrentNode;
/*



int m_nCurrentNode;


m_grid->findpath(m_startPos, m_endPos, m_path


vector2 dest = m_Path[m_currentNode];
vector2 direction = Dest - m_postition
direxction.normalize();
m_posiotn + m_position + direction * 100(speed) * deltaTime;


if((dest -m_postion).magnitude() < 10)
{
m_currentNode++
if(m_currentNode >= m_path.size())
	returns to
	m_currentNode = 0;
}
*/

//Change pos in player to vector2

//




/*
Going to use a global path towatds goal to hopefully make an 
'interesting' interaction between player and enemy agents.



I am going to use the path the player sets to navigate an area which
is only being drawn around a certain radius. (line of sight) 4 nodes?
If a node is blocked nothing is shown.

The player will only be able to set paths to locations that can be seen.

The enemy/s will spawn in a random location pause for a few seconds and query
the global path try to path towards the closest point along the path from its location
with some degree of inacuracy.

It will then pause and then repeat.

If the enemy agent is within a certain number of nodes to the player agent
its new destination will be the player.

Once it is outside of the detected range it will head to the players last location.
Pause and move around its neighbours for a moment and then continue with following
the global path rules.



The Enemy agents will move slower 0.75? of the player speed resulting in the 
player being able to escape.

the enememy will need a to be able to change states based on factors.

state 0 (wait)
Enemy waiting.
Still detecting around itself.

state 1 (seek)
Aquired path towards players current destination/previous destination.
Still detecting around itself.

state 2 (chase)
Aquiring path directly to the player while it is in sight.
If player out of line of sight(3 nodes?) Will stop updating 
destination towards player and will head towards last known co-ordinates.

state 3 (investigate)
Will check around 2 nodes around last destination
a random number of times.(2 - 4)
Still detecting around itself.

state 4 (random)
Aquire a random valid destination and move towards it.
Will only do after chase to allow player some breathing room.
Still detecting around itself.



Consider creating a base class for agents.
Both player and enemy will inherit from them.
Enemy will need some ckind or random number generator

*/
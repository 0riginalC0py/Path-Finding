#pragma once

#include "Renderer2D.h"
#include "Texture.h"
#include "Vector2.h"
#include <vector>
#include "BB.h"



class Player
{
public:
	Player();
	~Player();

	void Update(float deltaTime, BB& levelManager);
	void Draw(aie::Renderer2D* renderer);

	Vector2 GetV2pos();

private:

	Vector2 m_start;
	Vector2 m_end;

	aie::Texture* m_texture;
	Vector2 m_position;
	
	//If false will get new position.
	//bool m_findPosition;

	//::vector<Vector2> m_playerPath;

};


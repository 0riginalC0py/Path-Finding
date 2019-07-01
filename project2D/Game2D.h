#pragma once

#include "Game.h"
#include "Renderer2D.h"
#include "Vector2.h"
#include <vector>
#include "Grid.h"

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
	aie::Texture*		m_texture;
	aie::Texture*		m_texture2;
	aie::Font*			m_font;

	Grid* m_pGrid;
	Vector2 m_v2StartPos;
	Vector2 m_v2EndPos;
	std::vector<Vector2> m_Path;

	// Player.
	Player* m_Player;
};
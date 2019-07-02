#pragma once

#include "Renderer2D.h"
#include "Texture.h"
#include "Vector2.h"
#include "Grid.h"
#include "DebugList.h"

class Player
{
public:
	Player(Grid* pGrid, DebugList* pDebugList);
	~Player();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* renderer);

private:
	aie::Texture* m_texture;

	Vector2 m_v2Position;
	float m_fRotation;

	Vector2 m_v2StartPos;
	Vector2 m_v2EndPos;
	std::vector<Vector2> m_Path;

	DebugList* m_pDebug;

	Grid* m_pGrid;
	bool m_bRecalculate;
	bool m_bPathFinding;
};
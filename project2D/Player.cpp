#include "Player.h"
#include "Input.h"
#include "Node.h"

Player::Player(Grid* pGrid)
{
	// Load the player's sprite.
	m_texture = new aie::Texture("./textures/ship.png");

	// Set the player's position.
	m_v2Position.x = 0.0f;
	m_v2Position.y = 0.0f;
	m_pGrid = pGrid;
	m_bPathFinding = false;
}

Player::~Player()
{
	// Delete the player's sprite.
	delete m_texture;
	m_texture = nullptr;
}

void Player::Update(float deltaTime)
{
	// Update input for the player.
	aie::Input* input = aie::Input::GetInstance();
	Vector2 v2MousePos;
	v2MousePos.x = input->GetMouseX();
	v2MousePos.y = input->GetMouseY();
	/*if (input->IsKeyDown(aie::INPUT_KEY_LEFT))
	{
		m_v2Position.x -= 500.0f * deltaTime;
	}
	if (input->IsKeyDown(aie::INPUT_KEY_RIGHT))
	{
		m_v2Position.x += 500.0f * deltaTime;
	}
	if (input->IsKeyDown(aie::INPUT_KEY_UP))
	{
		m_v2Position.y += 500.0f * deltaTime;
	}
	if (input->IsKeyDown(aie::INPUT_KEY_DOWN))
	{
		m_v2Position.y -= 500.0f * deltaTime;
	}*/

	//Pathfinding

	if (input->WasKeyPressed(aie::INPUT_KEY_S))
	{
		m_v2StartPos = v2MousePos;

		m_v2Position.x = m_v2StartPos.x;
		m_v2Position.y = m_v2StartPos.y;
	}

	if (input->WasKeyPressed(aie::INPUT_KEY_E))
	{
		m_v2EndPos = v2MousePos;
		m_bRecalculate = true;
	}

	if (input->WasKeyPressed(aie::INPUT_KEY_SPACE))
		m_bPathFinding = true;
	
	/*m_pGrid->FindPath(m_v2Position, m_v2EndPos, m_Path);*/
	if (m_bPathFinding)
	{
		if (m_bRecalculate)
		{
			if (m_pGrid->FindPath(m_v2Position, m_v2EndPos, m_Path))
			{
				m_bRecalculate = false;
			}
		}

		if (m_Path.size() > 1)
		{
			Vector2 dest = m_Path[1];

			Vector2 direction = dest - m_v2Position;
			direction.normalise();
			m_v2Position = m_v2Position + direction * 100 * deltaTime;

			m_fRotation = atan2f(direction.y, direction.x) - 1.5708f;

			if ((dest - m_v2Position).magnitude() < 10)
				m_bRecalculate = true;
		}
		else
		{
			m_v2EndPos = Vector2(rand() % 1000, rand() % 500);
			/*m_bPathFinding = false;*/
		}
		
		if (input->WasKeyPressed(aie::INPUT_KEY_BACKSPACE))
			m_bPathFinding = false;
		
	}
}


void Player::Draw(aie::Renderer2D* m_2dRenderer)
{
	// Draw the player's sprite.
	m_2dRenderer->DrawSprite(m_texture, m_v2Position.x, m_v2Position.y, 0.0f, 0.0f, m_fRotation);

	m_2dRenderer->SetRenderColour(0xFF2376FF);
	for (int i = 1; i < m_Path.size(); i++)
	{
		m_2dRenderer->DrawLine(m_Path[i - 1].x, m_Path[i - 1].y, m_Path[i].x, m_Path[i].y, 5.0f);
	}

	m_2dRenderer->SetRenderColour(0x3F2BA6FF);
	m_2dRenderer->DrawCircle(m_v2StartPos.x, m_v2StartPos.y, 5.0f);

	m_2dRenderer->SetRenderColour(0x24F856FF);
	m_2dRenderer->DrawCircle(m_v2EndPos.x, m_v2EndPos.y, 5.0f);

	m_2dRenderer->SetRenderColour(0xFFFFFFFF);
}
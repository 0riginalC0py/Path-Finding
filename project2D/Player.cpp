#include "Player.h"
#include "Input.h"



Player::Player()
{
	//Load the player's sprite.
	m_texture = new aie::Texture("./textures/ship.png");

	//Set the player's position.
	m_position.m_x = PLAYER_START_POSX;
	m_position.m_y = PLAYER_START_POSY;
	
	//m_findPosition = false;
}

Player::~Player()
{
	// Delete the player's sprite.
	delete m_texture;
	m_texture = nullptr;
}

void Player::Update(float deltaTime, BB& gameManager)
{
	aie::Input* input = aie::Input::GetInstance();
	if (input->WasKeyPressed(aie::INPUT_KEY_Q))
	{
		m_start = gameManager.v2MousePos;
	}
	if (input->WasKeyPressed(aie::INPUT_KEY_E))
	{
		m_end = gameManager.v2MousePos;
	}
	//Needs to be a limit to stop if the player is at location.
	
	gameManager.m_grid->FindPath(m_start, m_end, gameManager.m_globalPath);

	if (gameManager.m_globalPath.size() != 0)
	{
		if (/*m_findPosition == false*/true)
		{
			//m_findPosition = true;
			Vector2 dest = gameManager.m_globalPath[1];
			Vector2 direction = dest - m_position;
			direction.normalise();
			m_position = m_position + direction * PLAYER_SPEED * deltaTime;
			//Start position is now the player.
			m_start = m_position;
		}
		else
		{

		}
	}

	// Update input for the player.
	//aie::Input* input = aie::Input::GetInstance();
	//if (input->IsKeyDown(aie::INPUT_KEY_LEFT))
	//{
	//	m_posX -= 500.0f * deltaTime;
	//}
	//if (input->IsKeyDown(aie::INPUT_KEY_RIGHT))
	//{
	//	m_posX += 500.0f * deltaTime;
	//}
	//if (input->IsKeyDown(aie::INPUT_KEY_UP))
	//{
	//	m_posY += 500.0f * deltaTime;
	//}
	//if (input->IsKeyDown(aie::INPUT_KEY_DOWN))
	//{
	//	m_posY -= 500.0f * deltaTime;
	//}
}

void Player::Draw(aie::Renderer2D* renderer)
{
	// Draw the player's sprite.



	renderer->DrawSprite(m_texture, m_position.m_x, m_position.m_y);
}

Vector2 Player::GetV2pos()
{
	return m_position;
}
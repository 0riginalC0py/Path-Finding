#include "Game2D.h"

#include "Application.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Player.h"
#include "Grid.h"
#include "Vector2.h"
#include "Node.h"

#define GRID_WIDTH 38
#define GRID_HEIGHT 21

Game2D::Game2D(const char* title, int width, int height, bool fullscreen) : Game(title, width, height, fullscreen)
{
	// Initalise the 2D renderer.
	m_2dRenderer = new aie::Renderer2D();

	// Create some textures for testing.
	m_texture = new aie::Texture("./textures/hero.png");
	m_texture2 = new aie::Texture("./textures/rock_large.png");
	m_font = new aie::Font("./font/consolas.ttf", 24);

	m_pGrid = new Grid(GRID_WIDTH, GRID_HEIGHT);

	// Create a player object.
	m_Player = new Player(m_pGrid);

}

Game2D::~Game2D()
{
	// Delete player.
	delete m_Player;
	m_Player = nullptr;

	delete m_pGrid;
	// Deleted the textures.
	delete m_font;
	delete m_texture;
	delete m_texture2;

	// Delete the renderer.
	delete m_2dRenderer;
}

void Game2D::Update(float deltaTime)
{
	// Update the player.
	m_Player->Update(deltaTime);

	// Input example: Update the camera position using the arrow keys.
	aie::Input* input = aie::Input::GetInstance();
	Vector2 v2MousePos;
	v2MousePos.x = input->GetMouseX();
	v2MousePos.y = input->GetMouseY();

	////Pathfinding
	if (input->IsMouseButtonDown(0))
	{
		Node* pMouseNode = m_pGrid->GetNodeByPosition(v2MousePos);
		if (pMouseNode)
			pMouseNode->m_bBlocked = true;
	}
	if (input->IsMouseButtonDown(1))
	{
		Node* pMouseNode = m_pGrid->GetNodeByPosition(v2MousePos);
		if (pMouseNode)
			pMouseNode->m_bBlocked = false;
	}

	//if (input->WasKeyPressed(aie::INPUT_KEY_S))
	//	m_v2StartPos = v2MousePos;

	//if (input->WasKeyPressed(aie::INPUT_KEY_E))
	//	m_v2EndPos = v2MousePos;

	//m_pGrid->FindPath(m_v2StartPos, m_v2EndPos, m_Path);

	// Exit the application if escape is pressed.
	if (input->IsKeyDown(aie::INPUT_KEY_ESCAPE))
	{
		aie::Application* application = aie::Application::GetInstance();
		application->Quit();
	}
}

void Game2D::Draw()
{
	aie::Application* application = aie::Application::GetInstance();
	float time = application->GetTime();

	// Wipe the screen to clear away the previous frame.
	application->ClearScreen();

	// Prepare the renderer. This must be called before any sprites are drawn.
	m_2dRenderer->Begin();

	m_pGrid->Draw(m_2dRenderer);

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

	// Draw the player.
	m_Player->Draw(m_2dRenderer);

	//// Draw a thin line.
	//m_2dRenderer->DrawLine(150.0f, 400.0f, 250.0f, 500.0f, 2.0f);

	//// Draw a sprite
	//m_2dRenderer->DrawSprite(m_texture2, 200.0f, 200.0f);

	//// Draw a moving purple circle.
	//m_2dRenderer->SetRenderColour(1.0f, 0.0f, 1.0f, 1.0f);
	//m_2dRenderer->DrawCircle(sin(time) * 100.0f + 450.0f, 200.0f, 50.0f);

	//// Draw a rotating sprite with no texture, coloured yellow.
	//m_2dRenderer->SetRenderColour(1.0f, 1.0f, 0.0f, 1.0f);
	//m_2dRenderer->DrawSprite(nullptr, 700.0f, 200.0f, 50.0f, 50.0f, time);
	//m_2dRenderer->SetRenderColour(1.0f, 1.0f, 1.0f, 1.0f);

	//// Demonstrate animation.
	//float animSpeed = 10.0f;
	//int frame = ((int)(time * animSpeed) % 6);
	//float size = 1.0f / 6.0f;
	//m_2dRenderer->SetUVRect(frame * size, 0.0f, size, 1.0f);
	//m_2dRenderer->DrawSprite(m_texture, 900.0f, 200.0f, 100.0f, 100.0f);
	//m_2dRenderer->SetUVRect(0.0f, 0.0f, 1.0f, 1.0f);
	
	// Draw some text.
	float windowHeight = (float)application->GetWindowHeight();
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", application->GetFPS());
	m_2dRenderer->DrawText2D(m_font, fps, 15.0f, windowHeight - 32.0f);
	//m_2dRenderer->DrawText2D(m_font, "Arrow keys to move.", 15.0f, windowHeight - 64.0f);
	//m_2dRenderer->DrawText2D(m_font, "WASD to move camera.", 15.0f, windowHeight - 96.0f);
	//m_2dRenderer->DrawText2D(m_font, "Press ESC to quit!", 15.0f, windowHeight - 128.0f);

	// Done drawing sprites. Must be called at the end of the Draw().
	m_2dRenderer->End();
}
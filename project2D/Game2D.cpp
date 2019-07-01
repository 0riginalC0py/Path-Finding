#include "Game2D.h"

#include "Application.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Player.h"
#include "Node.h"




Game2D::Game2D(const char* title, int width, int height, bool fullscreen) : Game(title, width, height, fullscreen)
{
	// Initalise the 2D renderer.
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 24);
	// Create a player object.
	m_Player = new Player();
	//Initialisation of gameManger. 
	//Might be better to do it in the class itself.
	m_levelManager.m_grid = new Grid(GRID_WIDTH, GRID_HEIGHT);
	
	//m_gameManager.m_totalSquares = GRID_WIDTH * GRID_HEIGHT;
}

Game2D::~Game2D()
{
	// Delete player.
	delete m_Player;
	m_Player = nullptr;

	// Deleted the textures.
	delete m_font;
	// Delete the renderer.
	delete m_2dRenderer;
	//delete m_Grid;
	delete m_levelManager.m_grid;
}

void Game2D::Update(float deltaTime)
{
	//----------------------------------------------------
	//Allow input.
	//Passed pointer passed into updates that require input
	//----------------------------------------------------

	aie::Input* input = aie::Input::GetInstance();
	
	//----------------------------------------------------
	//Get the position of camera.
	//Needs to be passed into functions to be added to 
	//anything that requires interaction with mouse.
	//Also used to set camera on position on player sprite.
	//----------------------------------------------------

	m_levelManager.m_camera = m_Player->GetV2pos();
	
	//----------------------------------------------------
	//Left in as example for camera being independant from
	//player.
	//----------------------------------------------------
	/*
	float camPosX;
	float camPosY;
	m_2dRenderer->GetCameraPos(camPosX, camPosY);

	if (input->IsKeyDown(aie::INPUT_KEY_W))
		camPosY += 500.0f * deltaTime;

	if (input->IsKeyDown(aie::INPUT_KEY_S))
		camPosY -= 500.0f * deltaTime;

	if (input->IsKeyDown(aie::INPUT_KEY_A))
		camPosX -= 500.0f * deltaTime;

	if (input->IsKeyDown(aie::INPUT_KEY_D))
		camPosX += 500.0f * deltaTime;
		
	*/
	

	//----------------------------------------------------
	//Sets camera position with the offsets.
	//Located within header.
	//----------------------------------------------------

	m_2dRenderer->SetCameraPos(m_levelManager.m_camera.m_x - WINDOW_OFFSET_X, m_levelManager.m_camera.m_y - WINDOW_OFFSET_Y);

	//----------------------------------------------------
	//Gets the mouse position for interaction with grid.
	//Seperate from camera but camera needs to be added to
	//correctly calculate position. Offsets of window also
	//needed.
	//----------------------------------------------------

	m_levelManager.v2MousePos.m_x = (float)input->GetMouseX() + m_levelManager.m_camera.m_x - WINDOW_OFFSET_X;
	m_levelManager.v2MousePos.m_y = (float)input->GetMouseY() + m_levelManager.m_camera.m_y - WINDOW_OFFSET_Y;

	//----------------------------------------------------
	//A testament to failure. Ask Finn.
	#define INV_ROOT_TWO 4.54568795135446f
	//----------------------------------------------------


	//----------------------------------------------------
	//Checks input for mouse buttons are pressed for interatcions
	//with grid. ie. Blocking/Unblocking boxes on grid
	//Needs mouse position to get correct Node.
	//----------------------------------------------------

	//For blocking Nodes.
	if (input->IsMouseButtonDown(0))
	{
		Node* mouseNode = m_levelManager.m_grid->GetNodeByPos(m_levelManager.v2MousePos);
		if (mouseNode)
		{
			mouseNode->m_blocked = true;
		}
	}
	//For unblocking Nodes.
	if (input->IsMouseButtonDown(1))
	{
		Node* mouseNode = m_levelManager.m_grid->GetNodeByPos(m_levelManager.v2MousePos);
		if (mouseNode)
		{
			mouseNode->m_blocked = false;
		}
	}

	//----------------------------------------------------
	//Checks input and places a start or end point.
	//Requires mouse position and start and end variables.
	//Moved into player.
	//----------------------------------------------------

	//if (input->WasKeyPressed(aie::INPUT_KEY_Q))
	//{
	//	m_start = v2MousePos;
	//}
	//if (input->WasKeyPressed(aie::INPUT_KEY_E))
	//{
	//	m_end = v2MousePos;
	//}

	//----------------------------------------------------
	//Path is calculated based on start and end.
	//Function handles all valid information.
	//Path would then need to be passed into player
	//from here to have player travel down path.
	//Path is passed in as a reference.
	//Moved into player.
	//----------------------------------------------------

	//m_Grid->FindPath(m_start, m_end, m_globalPath);
	
	//----------------------------------------------------
	//Saveing and loading done here.
	//Consider moving into gameManger.
	//----------------------------------------------------
	if(input->WasKeyPressed(aie::INPUT_KEY_J))
		m_levelManager.m_grid->Save();

	if(input->WasKeyPressed(aie::INPUT_KEY_L))
		m_levelManager.m_grid->Load();
	//----------------------------------------------------
	//Update function on player.
	//Needs the path to be able to move towards it.
	//Needs camera if any interactions are handled via mouse.
	//Trialing passing in setup information in a game manger
	//for global variables.
	//Check 'BB.h'
	//----------------------------------------------------
	
	m_Player->Update(deltaTime, m_levelManager);
	
	//----------------------------------------------------
	//Updates debug toggles.
	//Very ugly and I don't like it.
	//----------------------------------------------------
	m_levelManager.m_debugList.Update();

	//----------------------------------------------------
	//Exit the application if escape is pressed.
	//Consdier moving into game manager.
	//----------------------------------------------------
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

	//----------------------------------------------------
	// Wipe the screen to clear away the previous frame.
	//----------------------------------------------------
	
	application->ClearScreen();

	//----------------------------------------------------
	// Prepare the renderer. This must be called before any sprites are drawn.
	//----------------------------------------------------
	
	m_2dRenderer->Begin();

	//----------------------------------------------------
	//Draw Nodes as squares and lines between Nodes.
	//Removing will remove nodes in any state.
	//Change Square size in cpp
	//----------------------------------------------------

	m_levelManager.m_grid->Draw(m_2dRenderer, m_levelManager);

	//----------------------------------------------------
	//Draw lines along destination.
	//Remove if no lines wanted.
	//For debug purposes. 
	//Consider turning on/off via a key press.
	//Consider moving into game manager.
	//----------------------------------------------------

	if (m_levelManager.m_debugList.item[2])
	{
		for (int i = 1; i < m_levelManager.m_globalPath.size(); i++)
		{
			m_2dRenderer->DrawLine(m_levelManager.m_globalPath[i - 1].m_x, m_levelManager.m_globalPath[i - 1].m_y,
				m_levelManager.m_globalPath[i].m_x, m_levelManager.m_globalPath[i].m_y);
		}
	}

	//----------------------------------------------------
	//Draw the player.
	//----------------------------------------------------

	m_Player->Draw(m_2dRenderer);

	//----------------------------------------------------
	//Draw some text.
	//Left in as example.
	//----------------------------------------------------

	float windowHeight = (float)application->GetWindowHeight();
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", application->GetFPS());
	m_2dRenderer->DrawText2D(m_font, fps, 15.0f, windowHeight - 32.0f);
	m_2dRenderer->DrawText2D(m_font, "Press ESC to quit!", 15.0f, windowHeight - 128.0f);

	// Done drawing sprites. Must be called at the end of the Draw().
	m_2dRenderer->End();
}
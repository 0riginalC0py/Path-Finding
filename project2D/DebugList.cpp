#include "DebugList.h"
#include "Application.h"


//----------------------------------------------------
//This class was made to centralise all debug toggles.
//Very poorly implemented :( 
//It does do the job however and initialises values
//correctly.
//Note that the existence of the class could be nulled
//completly and moved into game manager rather than
//being a class within game manager as game manager
//handles is almost neccesary for any debug info.
//Cosider that in future or refactor.
//----------------------------------------------------
//Upon further reflection this has become almost a game
//manager.
//----------------------------------------------------

DebugList::DebugList()
{
	for (int i = 0; i < DEBUG_ITEMS; i++)
		item[i] = false;
}

DebugList::~DebugList()
{

}

void DebugList::Update()
{
	aie::Input* input = aie::Input::GetInstance();
	aie::Application* application = aie::Application::GetInstance();
	if (input->WasKeyPressed(aie::INPUT_KEY_1))
	{
		if (item[0])
			item[0] = false;
		else
			item[0] = true;
	}
	if (input->WasKeyPressed(aie::INPUT_KEY_2))
	{
		if (item[1])
			item[1] = false;
		else
			item[1] = true;
	}
	if (input->WasKeyPressed(aie::INPUT_KEY_3))
	{
		if (item[2])
			item[2] = false;
		else
			item[2] = true;
	}

	if (input->IsKeyDown(aie::INPUT_KEY_ESCAPE))
	{
		aie::Application* application = aie::Application::GetInstance();
		application->Quit();
	}
}
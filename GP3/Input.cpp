#include "Input.h"

bool* Input::m_keyStates = new bool[256];

void Input::Init()
{
	for (int i = 0; i < 255; i++)
	{
		Input::m_keyStates[i] = false;
	}
}

bool Input::KeyPressed(unsigned char key)
{
	return Input::m_keyStates[key];
}
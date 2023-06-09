#include "EventManager.h"
#include "Engine.h"
#include <cstring>
#include <iostream>

void EventManager::Init()
{
	s_keysCurr = SDL_GetKeyboardState(&s_numKeys);
	s_keysLast = new Uint8[s_numKeys];
	std::memcpy(s_keysLast, s_keysCurr, s_numKeys);
	s_mouseCurr = SDL_GetMouseState(&s_mousePos.x, &s_mousePos.y);
	s_mouseLast = s_mouseCurr;
	std::cout << "EventManager init success!" << std::endl;
}

void EventManager::HandleEvents()
{
	SDL_Event event;
	
	std::memcpy(s_keysLast, s_keysCurr, s_numKeys);
	s_mouseLast = s_mouseCurr;
	s_lastKeyDown = s_lastKeyUp = -1;

	while (SDL_PollEvent(&event)) // Pump events invoked.
	{
		switch (event.type) // Parse some global events.
		{
			case SDL_QUIT: // User pressed window's 'x' button.
				Engine::Instance().SetRunning(false);
				break;
			case SDL_KEYDOWN:
				s_lastKeyDown = event.key.keysym.sym;
				break;
			case SDL_KEYUP:
				s_lastKeyUp = event.key.keysym.sym;
				if (event.key.keysym.sym == SDLK_ESCAPE)
					Engine::Instance().SetRunning(false);
				break;
		}
	}
	s_keysCurr = SDL_GetKeyboardState(&s_numKeys);
	s_mouseCurr = SDL_GetMouseState(&s_mousePos.x, &s_mousePos.y);
}

bool EventManager::KeyHeld(const SDL_Scancode key)
{
	if (s_keysCurr != nullptr)
	{
		if (s_keysCurr[key] == 1)
			return true;
		else
			return false;
	}
	return false;
}

bool EventManager::KeyPressed(const SDL_Scancode key)
{
	return (s_keysCurr[key] > s_keysLast[key]);
}

bool EventManager::KeyReleased(const SDL_Scancode key)
{
	return (s_keysCurr[key] < s_keysLast[key]);
}

int EventManager::LastKeyDown()
{
	return s_lastKeyDown;
}

int EventManager::LastKeyUp()
{
	return s_lastKeyUp;
}

bool EventManager::MouseHeld(const int btn)
{
	if (btn >= 1 && btn <= 3)
		return (s_mouseCurr & SDL_BUTTON(btn));
	else
		return false;
}

bool EventManager::MousePressed(const int btn)
{
	return ((s_mouseCurr & SDL_BUTTON(btn)) > (s_mouseLast & SDL_BUTTON(btn)));
}

bool EventManager::MouseReleased(const int btn)
{
	return ((s_mouseCurr & SDL_BUTTON(btn)) < (s_mouseLast & SDL_BUTTON(btn)));
}

SDL_Point& EventManager::GetMousePos()
{
	return s_mousePos;
}

void EventManager::SetCursor(const SDL_SystemCursor& cursor)
{
	SDL_FreeCursor(s_cursor);
	s_cursor = SDL_CreateSystemCursor(cursor);
	SDL_SetCursor(s_cursor);
}

void EventManager::Quit()
{
	delete s_keysLast;
	SDL_FreeCursor(s_cursor);
}

const Uint8* EventManager::s_keysCurr = nullptr;
Uint8* EventManager::s_keysLast;
int EventManager::s_numKeys;

int EventManager::s_lastKeyDown;
int EventManager::s_lastKeyUp;
SDL_Point EventManager::s_mousePos = { 0,0 };
Uint32 EventManager::s_mouseCurr;
Uint32 EventManager::s_mouseLast;

SDL_Cursor* EventManager::s_cursor;
// #pragma once
#ifndef __ENGINE_H__
#define __ENGINE_H__
#include <SDL.h>
#include <SDL_image.h>
#include <chrono>
#include <vector>
#include <map>
#include <string>
#include <SDL_mixer.h>

using namespace std;

const int WIDTH = 1536;
const int HEIGHT = 768;
const int FPS = 120;
const int PAUSE_WIDTH = 768;
const int PAUSE_HEIGHT = 384;


class Engine
{
public: 
	int Run();
	static Engine& Instance();
	static map<std::string, Mix_Music*> backgroundMusic; 
	bool KeyDown(SDL_Scancode);
	double GetDeltaTime();
	void SetRunning(bool run);

	
	SDL_FPoint m_mousePosition;
private:
	Engine();
	// For fixed timestep.
	chrono::time_point<chrono::steady_clock> m_start, m_end;
	chrono::duration<double> m_diff;
	double m_fps; // Changed to double.

	const Uint8* m_pKeystates;
	bool m_isRunning;

	

	chrono::time_point<chrono::steady_clock> lastFrameTime, thisFrameTime; // Cleaned this up.
	chrono::duration<double> lastFrameDuration;
	double deltaTime;

	int Init(const char*, const int, const int, const int, const int, const int);
	void HandleEvents();
	void Wake();
	void Update();
	void Sleep();
	void Render();
	void Clean();	
};

#endif

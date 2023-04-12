#include "ScrollingBackground.h"
#include "TextureManager.h"
#include "Engine.h"

ScrollingBackground::ScrollingBackground()
{
	m_backgrounds.reserve(8);
	// First background
	m_backgrounds.push_back(new Background({ 0, 0, WIDTH, HEIGHT }, {0.0f, 0.0f, WIDTH, HEIGHT }, 0.5f,
		"../Assets/img/country-platform-back.png", "menuBG1"));
	m_backgrounds.push_back(new Background({ 0, 0, WIDTH, HEIGHT }, { WIDTH, 0.0f, WIDTH, HEIGHT }, 0.5f,
		"../Assets/img/country-platform-back.png", "menuBG12"));

	m_backgrounds.push_back(new Background({ 0, 0, WIDTH, HEIGHT }, { 0.0f, 0.0f, WIDTH, HEIGHT }, 2.0f,
		"../Assets/img/country-platform-forest.png", "towersBG2"));
	m_backgrounds.push_back(new Background({ 0, 0, WIDTH, HEIGHT }, { WIDTH, 0.0f, WIDTH, HEIGHT }, 2.0f,
		"../Assets/img/country-platform-forest.png", "towersBG22"));

	// Second background
	
	
	for (int i = 0; i < 18; i++)
	{
		m_backgrounds.push_back(new Background({ 0, 0, 384, 224 }, { static_cast<float>(128 * i), 512 - 64, 328, 328 }, 0.1f,
			"../Assets/img/country-platform-tiles-example.png", "Floor"));

	}
	
	
}

ScrollingBackground::~ScrollingBackground()
{
	for (auto background : m_backgrounds)
	{
		delete background;
		background = nullptr;
	}
	
	m_backgrounds.clear();
	m_backgrounds.shrink_to_fit();
}

void ScrollingBackground::Update()
{
	for (const auto background : m_backgrounds)
	{
		background->Update();
		background->m_playerSpeed = playerSpeed;
	}
}

void ScrollingBackground::Render()
{
	for (const auto background : m_backgrounds)
		background->Render();
}
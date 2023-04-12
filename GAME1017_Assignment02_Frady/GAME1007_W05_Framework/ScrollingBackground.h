#pragma once
#ifndef __SCROLLING_BACKGROUND_H__
#define __SCROLLING_BACKGROUND_H__

#include "GameObject.h"
#include "Background.h"
#include <vector>

class ScrollingBackground : public GameObject
{
public:
	ScrollingBackground();
	~ScrollingBackground();
	void Update();
	void Render();

	float playerSpeed = 0.0f;
private:
	std::vector<Background*> m_backgrounds;
};
#endif //!__SCROLLING_BACKGROUND_H__
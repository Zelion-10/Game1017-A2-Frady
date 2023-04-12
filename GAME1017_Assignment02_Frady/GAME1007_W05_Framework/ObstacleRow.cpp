#include "ObstacleRow.h"
#include "RenderManager.h"
#include "TextureManager.h"

ObstacleRow::ObstacleRow() :m_gapCtr(0), m_gapMax(3)
{
	 /*Create the vector now.*/
	for (int i = 0; i < 1; i++)
	{
		auto obst = new Obstacle({ 128.0f * i * 10, 384.0f, 128.0f, 128.0f }, false, nullptr);
		obst->SetIsHazard(true);
		m_obstacles.push_back(obst);
	}
	m_obstacles.shrink_to_fit();

	// Load the textures
	TEMA::Load("../Assets/img/Robot1.png", "roller");
	TEMA::Load("../Assets/img/Robot2.png", "bug");
	TEMA::Load("../Assets/img/Robot3.png", "fly");


}

void ObstacleRow::Update()
{
	for (auto obstacle : m_obstacles)
	{
		
		if (obstacle != nullptr) 
		{
			if (obstacle->GetPos().x <= 0 - 128.0f)
			{
				delete m_obstacles[0];
				m_obstacles[0] = nullptr;
				m_obstacles.erase(m_obstacles.begin());

				if (m_gapCtr++ % m_gapMax == 0)
				{
					PickRandomObstacle();
					Obstacle* obst;
					switch (curObstacle)
					{
					case FLY_BUG:
					
						obst = new Obstacle({ 0 + 128.0f * 10, 384.0f, 128.0f, 168.0f }, true, new Image({ 0, 0, 110, 168 }, { 128 / 2, -(168 / 2), 110, 168 }, "fly"));
						obst->SetIsHazard(true);
						m_obstacles.push_back(obst);;
						break;
					case Bug:
						obst = new Obstacle({ 0 + 128.0f * 10, 384.0f, 128.0f, 168.0f }, true, new Image({ 0, 0, 110, 168 }, { 128 / 2, -(168 / 2), 110, 168 }, "bug"));
						obst->SetIsHazard(true);
						m_obstacles.push_back(obst);
						break;
					case Roller:

						obst = new Obstacle({ 0 + 128.0f * 10, 384.0f, 128.0f, 168.0f }, true, new Image({ 0, 0, 110, 168 }, { 128 / 2, -(168 / 2), 110, 168 }, "roller"));
						obst->SetIsHazard(true);
						m_obstacles.push_back(obst);
						break;
					}
				}
				else
				{
					auto obst = new Obstacle({ 0 + 128.0f * 10, 384.0f, 110.0f, 184.0f }, true, new Image({ 0, 0, 1280, 720 }, { 0, -184, 110, 184 }, "fly"));
					obst->SetIsHazard(false);
					m_obstacles.push_back(obst);
				}
			}
			else
			{
				obstacle->Update();
			}
		}
	}
}

void ObstacleRow::Render()
{
	// Blue line under obstacles.
	SDL_SetRenderDrawColor(REMA::GetRenderer(), 0, 0, 255, 255);
	// Render the obstacles.
	for (const auto obstacle : m_obstacles)
	{
		if (obstacle != nullptr) 
		{
			obstacle->Render();
		}
	}
}





void ObstacleRow::PickRandomObstacle()
{
	curObstacle = static_cast<CurrentObstacle>(rand() % static_cast<int>(CurrentObstacle::NUM_OBSTACLES));
}
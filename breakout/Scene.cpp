#include "Scene.h"


Scene::Scene(Game& game) : m_game(game)
{
}

Game& Scene::getGameRef()
{
	return m_game;
}

#include "IScene.h"

IScene::IScene(Game* game) : m_game(game)
{
}

Game* IScene::getGameRef()
{
	return m_game;
}

#pragma once

#include <string>
#include <map>
#include <vector>

#include "BrickType.h"

#include "tinyxml2.h"
using namespace tinyxml2;

using BricksLayout = std::vector<std::vector<char>>;
using BrickTypesMap = std::map<char, BrickType>;

class Level
{
public:
	unsigned int getRowCount() const;
	unsigned int getColumnCount() const;
	unsigned int getRowSpacing() const;
	unsigned int getColumnSpacing() const;
	std::string getBackgroundTexture() const;

	BrickTypesMap &getBrickTypes();
	BricksLayout &getBricksLayout();

private:
	friend class LevelScene;
	friend class GameScene;

	Level(XMLElement* level_element);

	// properties
	unsigned int m_rowCount;
	unsigned int m_colCount;
	unsigned int m_rowSpacing;
	unsigned int m_colSpacing;
	std::string m_bgTextureName;

	// data
	BrickTypesMap m_brickTypes;
	BricksLayout m_bricksLayout;
};
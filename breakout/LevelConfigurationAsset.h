#pragma once

#include "IAsset.h"
#include "BrickType.h"

#include <string>
#include <variant>
#include <optional>
#include <vector>
#include <map>

// type helpers for brick type manipulation
using BricksLayout = std::vector<std::vector<char>>;
using BrickTypesMap = std::map<char, BrickType>;

class LevelConfigurationAsset :
    public IAsset
{
public:
    LevelConfigurationAsset();

	virtual void loadFromFile(const std::string& fpath) override;

	unsigned int getRowCount() const;
	unsigned int getColumnCount() const;
	unsigned int getRowSpacing() const;
	unsigned int getColumnSpacing() const;

	std::string getBackgroundTexture() const;
	std::string getPaddleTexture() const;
	std::string getBallTexture() const;

	float getPaddleSpeed() const;
	float getBallSpeed() const;

	BrickTypesMap& getBrickTypes();
	BricksLayout& getBricksLayout();

private:
	// properties
	unsigned int m_rowCount;
	unsigned int m_colCount;
	unsigned int m_rowSpacing;
	unsigned int m_colSpacing;

	// textures
	std::string m_bgTextureName;
	std::string m_paddleTextureName;
	std::string m_ballTextureName;

	// speed data
	float m_paddleSpeed;
	float m_ballSpeed;

	// data
	BrickTypesMap m_brickTypes;
	BricksLayout m_bricksLayout;
};


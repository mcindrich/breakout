#include "LevelConfigurationAsset.h"

LevelConfigurationAsset::LevelConfigurationAsset()
	: m_rowCount(0), m_colCount(0), m_rowSpacing(0), m_colSpacing(0), m_paddleSpeed(0), m_ballSpeed(0)
{
}

void LevelConfigurationAsset::loadFromFile(const std::string& fpath)
{
	auto document = XMLDocument(true, tinyxml2::COLLAPSE_WHITESPACE);

	document.LoadFile(fpath.c_str());

	auto level_element = document.FirstChildElement();

	// extract properties
	level_element->FindAttribute("RowCount")->QueryUnsignedValue(&m_rowCount);
	level_element->FindAttribute("ColumnCount")->QueryUnsignedValue(&m_colCount);
	level_element->FindAttribute("RowSpacing")->QueryUnsignedValue(&m_rowSpacing);
	level_element->FindAttribute("ColumnSpacing")->QueryUnsignedValue(&m_colSpacing);

	m_bgTextureName = level_element->FindAttribute("BackgroundTexture")->Value();
	m_paddleTextureName = level_element->FindAttribute("PaddleTexture")->Value();
	m_ballTextureName = level_element->FindAttribute("BallTexture")->Value();

	level_element->FindAttribute("PaddleSpeed")->QueryFloatValue(&m_paddleSpeed);
	level_element->FindAttribute("BallSpeed")->QueryFloatValue(&m_ballSpeed);

	// extract brick types
	auto brick_types_element = level_element->FirstChildElement("BrickTypes");
	auto brick_type_element = brick_types_element->FirstChildElement("BrickType");
	auto bricks_element = level_element->FirstChildElement("Bricks");

	// iterate brick types and create data structures
	while (brick_type_element) {
		// create a new brick type
		auto brick_type = BrickType(brick_type_element);
		m_brickTypes[brick_type.getId()] = brick_type;

		brick_type_element = brick_type_element->NextSiblingElement();
	}

	auto layout_text = bricks_element->GetText();
	m_bricksLayout.reserve(m_rowCount);

	for (unsigned i = 0; i < m_rowCount; i++) {
		m_bricksLayout.push_back(std::vector<char>());
		m_bricksLayout[i].reserve(m_colCount);
		for (unsigned j = 0; j < m_colCount; j++) {
			m_bricksLayout[i].push_back(layout_text[i * m_colCount + j + i]);
		}
	}
}

unsigned int LevelConfigurationAsset::getRowCount() const
{
	return m_rowCount;
}

unsigned int LevelConfigurationAsset::getColumnCount() const
{
	return m_colCount;
}

unsigned int LevelConfigurationAsset::getRowSpacing() const
{
	return m_rowSpacing;
}

unsigned int LevelConfigurationAsset::getColumnSpacing() const
{
	return m_colSpacing;
}

std::string LevelConfigurationAsset::getBackgroundTexture() const
{
	return m_bgTextureName;
}

std::string LevelConfigurationAsset::getPaddleTexture() const
{
	return m_paddleTextureName;
}

std::string LevelConfigurationAsset::getBallTexture() const
{
	return m_ballTextureName;
}

float LevelConfigurationAsset::getPaddleSpeed() const
{
	return m_paddleSpeed;
}

float LevelConfigurationAsset::getBallSpeed() const
{
	return m_ballSpeed;
}

BrickTypesMap& LevelConfigurationAsset::getBrickTypes()
{
	return m_brickTypes;
}

BricksLayout& LevelConfigurationAsset::getBricksLayout()
{
	return m_bricksLayout;
}

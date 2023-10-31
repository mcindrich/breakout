#include "Level.h"

#include <iostream>

Level::Level(XMLElement* level_element)
{
	// extract properties
	level_element->FindAttribute("RowCount")->QueryUnsignedValue(&m_rowCount);
	level_element->FindAttribute("ColumnCount")->QueryUnsignedValue(&m_colCount);
	level_element->FindAttribute("RowSpacing")->QueryUnsignedValue(&m_rowSpacing);
	level_element->FindAttribute("ColumnSpacing")->QueryUnsignedValue(&m_colSpacing);
	m_bgTextureName = level_element->FindAttribute("BackgroundTexture")->Value();

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

unsigned int Level::getRowCount() const
{
	return m_rowCount;
}

unsigned int Level::getColumnCount() const
{
	return m_colCount;
}

unsigned int Level::getRowSpacing() const
{
	return m_rowSpacing;
}

unsigned int Level::getColumnSpacing() const
{
	return m_colSpacing;
}

std::string Level::getBackgroundTexture() const
{
	return m_bgTextureName;
}

BrickTypesMap& Level::getBrickTypes()
{
	return m_brickTypes;
}

BricksLayout& Level::getBricksLayout()
{
	return m_bricksLayout;
}

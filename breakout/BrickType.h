#pragma once

#include <string>
#include <variant>
#include <optional>

#include <tinyxml2.h>
using namespace tinyxml2;

class BrickType
{
public:
	// needed for std::map
	BrickType();

	bool isInfinite() const;

	char getId() const;

	std::string getBrickTextureName() const;

	unsigned int getHitPoints() const;
	unsigned int getBreakScore() const;

	std::string getHitSoundName() const;
	std::string getBreakSoundName() const;

private:
	friend class LevelConfigurationAsset;
	friend class Level;
	BrickType(XMLElement* brick_element);

	char m_ID; // ID used for this brick type
	std::string m_textureName; // texture path for this brick type

	std::optional<unsigned int> m_hitPoints; // if nullopt - assume infinite
	std::string m_hitSoundName; // every brick has a hit sound

	std::optional<unsigned int> m_breakScore; // optional - impenetrable bricks don't have it
	std::optional<std::string> m_breakSoundName; // optional - impenetrable don't have it
};
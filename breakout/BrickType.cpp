#include "BrickType.h"

BrickType::BrickType() : m_ID(0)
{
}

bool BrickType::isInfinite() const
{
	return m_hitPoints == std::nullopt;
}

char BrickType::getId() const
{
	return m_ID;
}

std::string BrickType::getBrickTextureName() const
{
	return m_textureName;
}

unsigned int BrickType::getHitPoints() const
{
	if(!isInfinite()) return m_hitPoints.value();
	return -1;
}

unsigned int BrickType::getBreakScore() const
{
	if (!isInfinite()) return m_breakScore.value();
	return -1;
}

std::string BrickType::getHitSoundName() const
{
	return m_hitSoundName;
}

std::string BrickType::getBreakSoundName() const
{
	if (!isInfinite()) return m_breakSoundName.value();
	return std::string();
}

BrickType::BrickType(XMLElement* brick_element)
{
	m_ID = *brick_element->FindAttribute("Id")->Value();
	m_textureName = brick_element->FindAttribute("Texture")->Value();

	unsigned int hit_points, break_score;
	std::string break_sound;
	
	auto hit_points_attr = brick_element->FindAttribute("HitPoints");
	if (strcmp(hit_points_attr->Value(), "Infinite") != 0) {
		// normal brick - load also break score and break sound
		hit_points_attr->QueryUnsignedValue(&hit_points);
		m_hitPoints = hit_points;

		brick_element->FindAttribute("BreakScore")->QueryUnsignedValue(&break_score);
		m_breakScore = break_score;

		break_sound = brick_element->FindAttribute("BreakSound")->Value();
		m_breakSoundName = break_sound;
	}
	m_hitSoundName = brick_element->FindAttribute("HitSound")->Value();
}

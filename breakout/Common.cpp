#include "Common.h"

#include <cstdlib>

float randomFloatInRange(float min, float max)
{
	float r = (float)rand() / (float)RAND_MAX;
	return min + r * (max - min);
}
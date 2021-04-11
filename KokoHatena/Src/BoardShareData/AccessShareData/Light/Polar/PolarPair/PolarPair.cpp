#include "PolarPair.hpp"
#include "../../../../../MyLibrary/MyLibrary.hpp"


namespace Kokoha
{
	PolarPair::PolarPair(const Vec2& pos)
		: PolarAngle(vecToAngle(pos))
		, posPair(PolarPos(m_angle, pos.length()), PolarPos(m_angle, pos.length()))
	{
	}
}

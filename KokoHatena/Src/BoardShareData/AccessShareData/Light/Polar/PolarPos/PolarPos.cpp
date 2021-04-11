#include "PolarPos.hpp"
#include "../../../../../MyLibrary/MyLibrary.hpp"


namespace Kokoha
{
	PolarPos::PolarPos(const Vec2& pos)
		: PolarAngle(vecToAngle(pos))
		, m_distance(pos.length())
	{
	}


	Vec2 PolarPos::toOrthogonalPos(const Vec2& center) const
	{
		return center + m_distance * angleToVec(m_angle);
	}


	Optional<double> PolarPos::twoVecToLine(const PolarPos& p1, const PolarPos& p2, double angle)
	{
		const double a = p2.r()*Cos(p2.m_angle) - p1.r()*Cos(p1.m_angle);
		const double b = p1.r()*Sin(p1.m_angle) - p2.r()*Sin(p2.m_angle);
		const double c = p1.r()*p2.r()*Sin(p1.m_angle - p2.m_angle);
		const double d = a*Sin(angle) + b*Cos(angle);

		if (Abs(d) < 1e-5 || c / d < 0) { return none; }
		return c/d;
	}
}
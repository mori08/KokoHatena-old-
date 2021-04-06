#pragma once


#include "../PolarPos/PolarPos.hpp"


namespace Kokoha
{
	/// <summary>
	/// PolarPair�N���X
	/// �ɍ��W��2��(�p�x�͓���)
	/// </summary>
	class PolarPair : public PolarAngle
	{
	public:

		std::pair<PolarPos, PolarPos> posPair;

	public:

		PolarPair(double angle, double dist1, double dist2)
			: PolarAngle(angle)
			, posPair(PolarPos(angle, dist1), PolarPos(angle, dist2))
		{
		}

	};
}
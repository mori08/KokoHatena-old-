#pragma once


#include "../PolarPos/PolarPos.hpp"


namespace Kokoha
{
	/// <summary>
	/// PolarPairクラス
	/// 極座標を2つ(角度は同じ)
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
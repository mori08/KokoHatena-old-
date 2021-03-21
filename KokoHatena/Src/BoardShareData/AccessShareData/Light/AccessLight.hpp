#pragma once


#include "../StageData/StageData.hpp"


namespace Kokoha
{
	/// <summary>
	/// AccessLightクラス
	/// AccessBoardで使う光
	/// </summary>
	class AccessLight
	{
	private:

		// 光を表す円
		Circle m_circle;

		// 方向
		Vec2 m_direction;

		// 範囲(余弦)
		double m_cosin;

	public:

		AccessLight(const Circle& circle, const Vec2& direction, double cosin);

	public:

		void draw(const StageData& stageData) const;

	};
}
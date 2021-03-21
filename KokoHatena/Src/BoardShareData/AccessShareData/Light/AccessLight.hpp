#pragma once


#include "../StageData/StageData.hpp"


namespace Kokoha
{
	/// <summary>
	/// AccessLight�N���X
	/// AccessBoard�Ŏg����
	/// </summary>
	class AccessLight
	{
	private:

		// ����\���~
		Circle m_circle;

		// ����
		Vec2 m_direction;

		// �͈�(�]��)
		double m_cosin;

	public:

		AccessLight(const Circle& circle, const Vec2& direction, double cosin);

	public:

		void draw(const StageData& stageData) const;

	};
}
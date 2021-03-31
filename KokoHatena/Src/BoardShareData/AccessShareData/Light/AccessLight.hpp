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
		double m_direction;

		// �͈�
		double m_angle;

		// �F
		// TODO

	public:

		AccessLight(const Circle& circle, double direction, double angle);

	public:

		void draw(const StageData& stageData) const;

	private:

		/// <summary>
		/// �����̌��̍��W��ݒ�
		/// </summary>
		/// <param name="lightPosList"> �����������W���X�g </param>
		void setInitLightPos(std::list<Vec2>& lightPosList) const;

		/// <summary>
		/// �e�̕�����ݒ�
		/// </summary>
		/// <param name="lightPosList"> �����������W���X�g </param>
		/// <param name="rect"> �e�����钷���` </param>
		void setShadow(std::list<Vec2>& lightPosList,const RectF& rect) const;

	};
}
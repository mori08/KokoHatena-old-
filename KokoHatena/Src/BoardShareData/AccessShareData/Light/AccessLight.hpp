#pragma once


#include "../StageData/StageData.hpp"
#include "Polar/PolarPair/PolarPair.hpp"


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

	public:

		AccessLight(const Circle& circle, double direction, double angle);

	public:

		void draw(const StageData& stageData) const;

	private:

		/// <summary>
		/// �����̌��̍��W�̐ݒ�
		/// </summary>
		/// <param name="lightPosMap"> �����������W </param>
		void setInitLightPos(std::set<PolarPair>& lightPosSet) const;

		/// <summary>
		/// �e�̕�����ݒ�
		/// </summary>
		/// <param name="lightPosSet"> ���������ɍ��W���X�g </param>
		/// <param name="rect"> �e�����钷���` </param>
		void setShadow(std::set<PolarPair>& lightPosSet, const RectF& rect) const;

		/// <summary>
		/// ����`��
		/// </summary>
		/// <param name="lightPosSet"></param>
		void drawLight(std::set<PolarPair>& lightPosSet)const;

		/// <summary>
		/// �������r=m_circle.r�ƂȂ�p�x��T��
		/// </summary>
		/// <param name="p1"> �ɍ��Wp1 </param>
		/// <param name="p2"> �ɍ��Wp2 </param>
		/// <returns> �Ή�����p�x </returns>
		void getAngleFromLine(const PolarPos& p1, const PolarPos& p2, std::set<PolarPair>& lightPosSet) const;

		/// <summary>
		/// ���W�����̔z��ɒǉ�
		/// </summary>
		/// <param name="polar"> �ǉ�����ɍ��W </param>
		/// <param name="posAry"> ���W�̔z�� </param>
		void addToPosAry(PolarPos polar, Array<Vec2>& posAry)const;

	};
}
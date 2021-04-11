#pragma once

#include "../PolarAngle/PolarAngle.hpp"


namespace Kokoha
{
	/// <summary>
	/// PolarPos�N���X
	/// �ɍ��W
	/// </summary>
	class PolarPos : public PolarAngle
	{
	private:

		// ����
		double m_distance;

	public:

		/// <summary>
		/// �ɍ��W
		/// </summary>
		/// <param name="angle"> �p�x </param>
		/// <param name="distance"> ���� </param>
		PolarPos(double angle, double distance)
			: PolarAngle(angle)
			, m_distance(distance)
		{
		}

		/// <summary>
		/// �������W����ɍ��W�ւ̕ϊ�
		/// </summary>
		/// <param name="pos"> �������W </param>
		PolarPos(const Vec2& pos);

	public:

		/// <summary>
		/// �����̎擾
		/// </summary>
		/// <returns> ���� </returns>
		double r() const
		{
			return m_distance;
		}

		/// <summary>
		/// �����̍X�V
		/// </summary>
		/// <param name="r"> ���� </param>
		/// <remarks>
		/// ������m_distance��菬�����ꍇ�̂ݍX�V
		/// </remarks>
		void setR(double r)
		{
			m_distance = Min(m_distance, r);
		}

		/// <summary>
		/// �������W�֕ϊ�
		/// </summary>
		/// <param name="center"> ���S���W </param>
		/// <returns> �������W </returns>
		Vec2 toOrthogonalPos(const Vec2& center)const;

		/// <summary>
		/// 2�̋ɍ��W��ʂ钼��
		/// </summary>
		/// <param name="p1"> �ɍ��W1 </param>
		/// <param name="p2"> �ɍ��W2 </param>
		/// <param name="angle"> �p�x </param>
		/// <returns> �w�肵���p�x�ł̒����Ƃ̋��� ��_���Ȃ��Ȃ� none </returns>
		static Optional<double> twoVecToLine(const PolarPos& p1, const PolarPos& p2, double angle);

	};
}
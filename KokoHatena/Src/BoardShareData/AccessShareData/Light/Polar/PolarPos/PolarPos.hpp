#pragma once

#include "../PolarAngle/PolarAngle.hpp"
#include "../../../../../MyLibrary/MyLibrary.hpp"


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
		Vec2 toOrthogonalPos(const Vec2& center)const
		{
			return std::move(center + m_distance * angleToVec(m_angle));
		}

	};
}
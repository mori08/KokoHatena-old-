#pragma once


#include <Siv3D.hpp>


namespace Kokoha
{
	/// <summary>
	/// PolarAngle�N���X
	/// �ɍ��W�̊p�x
	/// �\�[�g�p�̊֐���ێ�
	/// </summary>
	class PolarAngle
	{
	private:

		// �p�x��r�p�̒萔
		static const int32 ANGLE_COMP = (int32)1e5;

	public:

		// �p�x
		const double m_angle;

	public:

		PolarAngle(double angle)
			: m_angle(angle)
		{
		}

		bool operator<(const PolarAngle& another)const
		{
			return int32(ANGLE_COMP * m_angle) < int32(ANGLE_COMP * another.m_angle);
		}

		bool operator==(const PolarAngle& another)const
		{
			return int32(ANGLE_COMP * m_angle) == int32(ANGLE_COMP * another.m_angle);
		}

	};
}
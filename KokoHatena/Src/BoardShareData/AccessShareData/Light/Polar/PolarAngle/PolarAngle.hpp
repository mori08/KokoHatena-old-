#pragma once


#include <Siv3D.hpp>


namespace Kokoha
{
	/// <summary>
	/// PolarAngleクラス
	/// 極座標の角度
	/// ソート用の関数を保持
	/// </summary>
	class PolarAngle
	{
	private:

		// 角度比較用の定数
		static const int32 ANGLE_COMP = (int32)1e5;

	public:

		// 角度
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
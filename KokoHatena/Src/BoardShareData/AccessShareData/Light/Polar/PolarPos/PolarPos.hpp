#pragma once

#include "../PolarAngle/PolarAngle.hpp"
#include "../../../../../MyLibrary/MyLibrary.hpp"


namespace Kokoha
{
	/// <summary>
	/// PolarPosクラス
	/// 極座標
	/// </summary>
	class PolarPos : public PolarAngle
	{
	private:

		// 距離
		double m_distance;

	public:

		/// <summary>
		/// 極座標
		/// </summary>
		/// <param name="angle"> 角度 </param>
		/// <param name="distance"> 距離 </param>
		PolarPos(double angle, double distance)
			: PolarAngle(angle)
			, m_distance(distance)
		{
		}

	public:

		/// <summary>
		/// 距離の取得
		/// </summary>
		/// <returns> 距離 </returns>
		double r() const
		{
			return m_distance;
		}

		/// <summary>
		/// 距離の更新
		/// </summary>
		/// <param name="r"> 距離 </param>
		/// <remarks>
		/// 引数がm_distanceより小さい場合のみ更新
		/// </remarks>
		void setR(double r)
		{
			m_distance = Min(m_distance, r);
		}

		/// <summary>
		/// 直交座標へ変換
		/// </summary>
		/// <param name="center"> 中心座標 </param>
		/// <returns> 直交座標 </returns>
		Vec2 toOrthogonalPos(const Vec2& center)const
		{
			return std::move(center + m_distance * angleToVec(m_angle));
		}

	};
}
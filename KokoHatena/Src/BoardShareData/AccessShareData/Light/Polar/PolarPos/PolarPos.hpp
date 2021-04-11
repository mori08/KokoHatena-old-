#pragma once

#include "../PolarAngle/PolarAngle.hpp"


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

		/// <summary>
		/// 直交座標から極座標への変換
		/// </summary>
		/// <param name="pos"> 直交座標 </param>
		PolarPos(const Vec2& pos);

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
		Vec2 toOrthogonalPos(const Vec2& center)const;

		/// <summary>
		/// 2つの極座標を通る直線
		/// </summary>
		/// <param name="p1"> 極座標1 </param>
		/// <param name="p2"> 極座標2 </param>
		/// <param name="angle"> 角度 </param>
		/// <returns> 指定した角度での直線との距離 交点がないなら none </returns>
		static Optional<double> twoVecToLine(const PolarPos& p1, const PolarPos& p2, double angle);

	};
}
#pragma once


#include "../StageData/StageData.hpp"
#include "Polar/PolarPair/PolarPair.hpp"


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
		double m_direction;

		// 範囲
		double m_angle;

	public:

		AccessLight(const Circle& circle, double direction, double angle);

	public:

		void draw(const StageData& stageData) const;

	private:

		/// <summary>
		/// 初期の光の座標の設定
		/// </summary>
		/// <param name="lightPosMap"> 光を示す座標 </param>
		void setInitLightPos(std::set<PolarPair>& lightPosSet) const;

		/// <summary>
		/// 影の部分を設定
		/// </summary>
		/// <param name="lightPosSet"> 光を示す極座標リスト </param>
		/// <param name="rect"> 影をつくる長方形 </param>
		void setShadow(std::set<PolarPair>& lightPosSet, const RectF& rect) const;

		/// <summary>
		/// 光を描画
		/// </summary>
		/// <param name="lightPosSet"></param>
		void drawLight(std::set<PolarPair>& lightPosSet)const;

		/// <summary>
		/// 線分上でr=m_circle.rとなる角度を探す
		/// </summary>
		/// <param name="p1"> 極座標p1 </param>
		/// <param name="p2"> 極座標p2 </param>
		/// <returns> 対応する角度 </returns>
		void getAngleFromLine(const PolarPos& p1, const PolarPos& p2, std::set<PolarPair>& lightPosSet) const;

		/// <summary>
		/// 座標を光の配列に追加
		/// </summary>
		/// <param name="polar"> 追加する極座標 </param>
		/// <param name="posAry"> 座標の配列 </param>
		void addToPosAry(PolarPos polar, Array<Vec2>& posAry)const;

	};
}
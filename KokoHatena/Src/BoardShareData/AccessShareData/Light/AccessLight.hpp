#pragma once


#include "../StageData/StageData.hpp"


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

		// 色
		// TODO

	public:

		AccessLight(const Circle& circle, double direction, double angle);

	public:

		void draw(const StageData& stageData) const;

	private:

		/// <summary>
		/// 初期の光の座標を設定
		/// </summary>
		/// <param name="lightPosList"> 光を示す座標リスト </param>
		void setInitLightPos(std::list<Vec2>& lightPosList) const;

		/// <summary>
		/// 影の部分を設定
		/// </summary>
		/// <param name="lightPosList"> 光を示す座標リスト </param>
		/// <param name="rect"> 影をつくる長方形 </param>
		void setShadow(std::list<Vec2>& lightPosList,const RectF& rect) const;

	};
}
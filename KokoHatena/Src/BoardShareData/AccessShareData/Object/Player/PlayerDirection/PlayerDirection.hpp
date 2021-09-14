#pragma once


#include <Siv3D.hpp>


namespace Kokoha
{
	/// <summary>
	/// AccessPlayerの進む向きを表示
	/// </summary>
	class PlayerDirection
	{
	private:

		// 表示する座標
		Vec2 m_pos;

		// 目的地
		Vec2 m_goal;

		// 色の不透明度
		double m_alpha;

		// 目的地を変更中か
		bool m_isChangingGoal;

	public:

		/// <summary>
		/// 入力
		/// </summary>
		/// <param name="playerPos"> プレイヤーの座標 </param>
		/// <param name="goalPos"> 目的地の座標 </param>
		/// <param name="isChangingGoal"> ゴールを変更中か </param>
		void input(const Vec2& playerPos, const Vec2& goalrPos, bool isChangingGoal);

		/// <summary>
		/// 更新
		/// </summary>
		void update();

		/// <summary>
		/// 描画
		/// </summary>
		void draw() const;

	};
}
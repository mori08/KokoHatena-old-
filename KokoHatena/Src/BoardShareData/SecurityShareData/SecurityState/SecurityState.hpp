#pragma once


#include <Siv3D.hpp>


namespace Kokoha
{
	/// <summary>
	/// SecurityStateクラス
	/// SecurityBoardの状態
	/// </summary>
	class SecurityState
	{
	public:

		virtual ~SecurityState() {};

		/// <summary>
		/// ボードを閉じたときの処理
		/// </summary>
		virtual void closeProcess() {};

		/// <summary>
		/// ボードの入力処理
		/// </summary>
		/// <param name="mouseLeftUp"> マウスの左クリック時の座標 </param> 
		virtual void input(Optional<Vec2> mouseUpPoint) = 0;

		/// <summary>
		/// ボードの更新処理
		/// </summary>
		virtual void update() = 0;

		/// <summary>
		/// ボードの描画処理
		/// </summary>
		virtual void draw()const = 0;

	};
}
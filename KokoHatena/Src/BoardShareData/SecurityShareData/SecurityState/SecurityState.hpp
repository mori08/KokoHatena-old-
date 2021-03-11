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
	private:

		const std::function<void()> m_closeProcess;

	public:

		SecurityState()
			: m_closeProcess([](){})
		{}

		SecurityState(const std::function<void()>& closeProcess)
			: m_closeProcess(closeProcess)
		{}

		virtual ~SecurityState() {};

		/// <summary>
		/// ボードを閉じたときの処理
		/// </summary>
		void closeProcess() const
		{
			m_closeProcess();
		}

		/// <summary>
		/// ボードの入力処理
		/// </summary>
		/// <param name="mouseLeftUp"> マウスの左クリック時の座標 </param> 
		virtual void input(Optional<Vec2> mouseUpPoint) = 0;

		/// <summary>
		/// ボードの更新処理
		/// </summary>
		/// <param name="mousePosInBoard"> ボードの内でのマウス座標 </param>
		virtual void update(const Vec2& cursorPosInBoard) = 0;

		/// <summary>
		/// ボードの描画処理
		/// </summary>
		virtual void draw()const = 0;

	};
}
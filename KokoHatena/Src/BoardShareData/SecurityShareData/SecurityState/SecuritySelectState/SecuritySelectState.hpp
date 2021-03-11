#pragma once


#include <Siv3D.hpp>
#include "../SecurityState.hpp"


namespace Kokoha
{
	/// <summary>
	/// SecutitySelectStateクラス
	/// 選択肢を選ばせ，その選択に応じた処理を行う
	/// </summary>
	class SecuritySelectState : public SecurityState
	{
	private:

		// Boardに表示する文(選択肢)
		const String m_text;

		// yesを選んだ時の処理
		const std::function<void()> m_yesFunc;

		// noを選んだ時の処理
		const std::function<void()> m_noFunc;

		// カーソルの座標
		Vec2 m_cursorPos;

	public:

		/// <summary>
		/// 選択肢を選ばせる状態
		/// </summary>
		/// <param name="text"> Boardに表示する文 </param>
		/// <param name="yesFunc"> yesを選んだ時の処理 </param>
		/// <param name="noFunc"> noを選んだ時の処理 </param>
		/// <param name="closeProcess"> 閉じたときの処理 </param>
		SecuritySelectState(const String& text, const std::function<void()>& yesFunc, const std::function<void()>& noFunc, const std::function<void()>& closeProcess);

	private:

		void input(Optional<Vec2>) override;

		void update(const Vec2& cursorPosInBoard) override;

		void draw() const override;

	private:

		const Rect& yesButton() const;

		const Rect& noButton() const;

	};
}
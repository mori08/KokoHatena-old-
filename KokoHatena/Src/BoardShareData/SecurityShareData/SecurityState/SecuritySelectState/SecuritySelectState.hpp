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

	public:

		/// <summary>
		/// 選択肢を選ばせる状態
		/// </summary>
		/// <param name="text"> Boardに表示する文 </param>
		/// <param name="yesFunc"> yesを選んだ時の処理 </param>
		/// <param name="noFunc"> noを選んだ時の処理 </param>
		SecuritySelectState(const String& text, std::function<void()> yesFunc, std::function<void()> noFunc);

	private:

		void input() override;

		void update() override;

		void draw() const override;

	};
}
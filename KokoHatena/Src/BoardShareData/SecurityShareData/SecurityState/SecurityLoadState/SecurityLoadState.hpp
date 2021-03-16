#pragma once


#include "../SecurityState.hpp"


namespace Kokoha
{
	/// <summary>
	/// SecurityLoadStateクラス
	/// ゲージを表示する状態
	/// </summary>
	class SecurityLoadState : public SecurityState
	{
	private:

		// Boardに表示するテキスト
		const String m_text;

		// 終了後に行う処理
		const std::function<void()> m_finishFunc;

	private:

		// 進捗状況(0 -> 1)
		double m_progress;

	public:

		SecurityLoadState(const String& text, const std::function<void()>& finishFunc, const std::function<void()>& closeFunc);

	private:

		void input(Optional<Vec2>) override;

		void update(const Vec2&) override;

		void draw() const override;

	};
}
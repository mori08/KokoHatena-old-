#pragma once


#include "../SecurityState.hpp"


namespace Kokoha
{
	/*
	* SecutiryTextStateクラス
	* 指定されたテキストを表示する状態
	*/
	class SecurityTextState : public SecurityState
	{
	private:

		// Boardに表示する文字
		const String m_text;

	public:

		SecurityTextState(const String& text);

	private:

		void input(Optional<Vec2>) override;

		void update(const Vec2&) override;

		void draw() const override;

	};
}
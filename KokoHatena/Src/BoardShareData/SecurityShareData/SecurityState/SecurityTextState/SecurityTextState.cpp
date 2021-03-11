#include "SecurityTextState.hpp"
#include "../../../../Config/Config.hpp"
#include "../../../../MyLibrary/MyLibrary.hpp"


namespace Kokoha
{
	SecurityTextState::SecurityTextState(const String& text)
		: m_text(text)
	{
	}


	void SecurityTextState::input(Optional<Vec2>)
	{
	}


	void SecurityTextState::update(const Vec2&)
	{
	}


	void SecurityTextState::draw() const
	{
		static const Point TEXT_POS = Config::get<Point>(U"Board.Security.Text.textPos");

		FontAsset(U"15")(m_text).draw(TEXT_POS, MyWhite);
	}

}
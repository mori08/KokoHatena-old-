#include "SecuritySelectState.hpp"
#include "../../../../Config/Config.hpp"


namespace Kokoha
{
	SecuritySelectState::SecuritySelectState(const String& text, std::function<void()> yesFunc, std::function<void()> noFunc)
		: m_text(text)
		, m_yesFunc(yesFunc)
		, m_noFunc(noFunc)
	{

	}


	void SecuritySelectState::input()
	{

	}


	void SecuritySelectState::update()
	{

	}


	void SecuritySelectState::draw() const
	{
		static const Point TEXT_POS = Config::get<Point>(U"Board.Security.Select.textPos");
		
		FontAsset(U"15")(m_text).draw(TEXT_POS);
	}
}

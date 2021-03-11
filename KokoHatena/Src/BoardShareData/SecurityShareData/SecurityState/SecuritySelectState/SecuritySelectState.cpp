#include "SecuritySelectState.hpp"
#include "../../../../Config/Config.hpp"
#include "../../../../MyLibrary/MyLibrary.hpp"


namespace Kokoha
{
	
	SecuritySelectState::SecuritySelectState(const String& text, const std::function<void()>& yesFunc, const std::function<void()>& noFunc, const std::function<void()>& closeProcess)
		: SecurityState(closeProcess)
		, m_text(text)
		, m_yesFunc(yesFunc)
		, m_noFunc(noFunc)
	{
		
	}


	void SecuritySelectState::input(Optional<Vec2> mouseUpPos)
	{
		if (!mouseUpPos) { return; }

		if (yesButton().contains(mouseUpPos.value()))
		{
			m_yesFunc();
		}

		if (noButton().contains(mouseUpPos.value()))
		{
			m_noFunc();
		}
	}


	void SecuritySelectState::update(const Vec2& cursorPosInBoard)
	{
		m_cursorPos = cursorPosInBoard;
	}


	void SecuritySelectState::draw() const
	{
		static const Point TEXT_POS = Config::get<Point>(U"Board.Security.Select.textPos");
		
		FontAsset(U"15")(m_text).draw(TEXT_POS, MyWhite);
		
		const bool isSelectedYes = yesButton().contains(m_cursorPos);
		const bool isSelectedNo  =  noButton().contains(m_cursorPos);

		yesButton().draw(isSelectedYes ? MyWhite : ColorF(0,0));
		FontAsset(U"15")(U"Yes").drawAt(yesButton().center(), isSelectedYes ? MyBlack : MyWhite);

		noButton().draw(isSelectedNo ? MyWhite : ColorF(0, 0));
		FontAsset(U"15")(U"No").drawAt(noButton().center(), isSelectedNo ? MyBlack : MyWhite);
	}


	const Rect& SecuritySelectState::yesButton() const
	{
		static const Rect YES_BUTTON = Config::get<Rect>(U"Board.Security.Select.yesButton");
		return YES_BUTTON;
	}


	const Rect& SecuritySelectState::noButton() const
	{
		static const Rect NO_BUTTON = Config::get<Rect>(U"Board.Security.Select.noButton");
		return NO_BUTTON;
	}
}

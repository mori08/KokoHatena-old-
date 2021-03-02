#include "SecurityWaitState.hpp"
#include "../../../../Config/Config.hpp"
#include<Siv3D.hpp>


namespace Kokoha
{
	void SecurityWaitState::input()
	{
	}

	void SecurityWaitState::update()
	{
	}

	void SecurityWaitState::draw() const
	{
		static const Point TEXT_POS = Config::get<Point>(U"Board.Security.Wait.textPos");

		FontAsset(U"15")(U"���̒[���͕ی삳��Ă��܂��D").drawAt(TEXT_POS);
	}
}

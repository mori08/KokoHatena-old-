#include "SecurityWaitState.hpp"
#include "../../../../Config/Config.hpp"
#include<Siv3D.hpp>


namespace Kokoha
{
	void SecurityWaitState::input(Optional<Vec2>)
	{
	}


	void SecurityWaitState::update(const Vec2&)
	{
	}


	void SecurityWaitState::draw() const
	{
		static const Point TEXT_POS = Config::get<Point>(U"Board.Security.Wait.textPos");

		FontAsset(U"15")(U"���̒[���͕ی삳��Ă��܂�").drawAt(TEXT_POS);
	}
}

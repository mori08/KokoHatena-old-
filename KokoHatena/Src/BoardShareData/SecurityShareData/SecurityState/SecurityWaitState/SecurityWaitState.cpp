#include "SecurityWaitState.hpp"
#include<Siv3D.hpp>


namespace Kokoha
{
	void SecurityWaitState::update()
	{

	}

	void SecurityWaitState::draw() const
	{
		FontAsset(U"15")(U"���̒[���͕ی삳��Ă��܂��D").draw(Point(0, 30));
	}
}

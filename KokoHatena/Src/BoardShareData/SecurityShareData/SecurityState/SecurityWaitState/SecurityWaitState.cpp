#include "SecurityWaitState.hpp"
#include<Siv3D.hpp>


namespace Kokoha
{
	void SecurityWaitState::update()
	{

	}

	void SecurityWaitState::draw() const
	{
		FontAsset(U"15")(U"この端末は保護されています．").draw(Point(0, 30));
	}
}

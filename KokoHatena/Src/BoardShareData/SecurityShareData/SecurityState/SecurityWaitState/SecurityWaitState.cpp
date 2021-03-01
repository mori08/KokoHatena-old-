#include "SecurityWaitState.hpp"
#include<Siv3D.hpp>


namespace Kokoha
{
	void SecurityWaitState::update()
	{

	}

	void SecurityWaitState::draw() const
	{
		FontAsset(U"15")(U"‚±‚Ì’[––‚Í•ÛŒì‚³‚ê‚Ä‚¢‚Ü‚·D").draw(Point(0, 30));
	}
}

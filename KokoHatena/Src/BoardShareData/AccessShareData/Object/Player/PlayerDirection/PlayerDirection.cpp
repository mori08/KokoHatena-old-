#include "PlayerDirection.hpp"
#include "../../../../../Config/Config.hpp"
#include "../../../../../MyLibrary/MyLibrary.hpp"


namespace Kokoha
{
	void PlayerDirection::input(const Vec2& playerPos, const Vec2& goalPos, bool isChangingGoal)
	{
		if (m_alpha > 1e-3) { return; }
	
		m_pos = playerPos;
		m_goal = goalPos;
		m_alpha = 1;
		m_isChangingGoal = isChangingGoal;
	}


	void PlayerDirection::update()
	{
		internalDividingPoint(m_pos, m_goal, 1e-3);

		if (m_pos.distanceFrom(m_goal) < 1)
		{
			internalDividingPoint(m_alpha, 0, 1e-2);
		}
	}


	void PlayerDirection::draw() const
	{
		static const double RADIUS = Config::get<double>(U"Board.Access.Object.Player.Direction.radius");
		Circle(m_pos, RADIUS).draw(ColorF(MyWhite).setA(m_alpha));
	}
}

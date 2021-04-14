#include "TestObject.hpp"
#include "../../../../MyLibrary/MyLibrary.hpp"


namespace Kokoha
{
	TestObject::TestObject(const Vec2& pos)
		: AccessObject(Circle(pos, 10), AccessObjectType::PLAYER)
	{
		goal = StageData::integerToPixel(Random(StageData::N - 1));
		direction = 0;
	}


	void TestObject::input(const Vec2&)
	{
		
	}


	void TestObject::update(AccessShareData& shareData)
	{
		const Vec2 movement = walkToGoalThroughCenter(60.0, goal, shareData);
		
		if (movement.isZero())
		{
			goal = StageData::integerToPixel(Random(StageData::N - 1));
		}
		else
		{
			internalDividingPoint(direction, direction + twoVecToAngle(angleToVec(direction), movement), 1e-1);
		}

		shareData.addLight(Circle(m_body.center, 240), direction, Math::Pi / 6);
	}


	void TestObject::draw() const
	{
		m_body.draw(MyBlack);
	}
}

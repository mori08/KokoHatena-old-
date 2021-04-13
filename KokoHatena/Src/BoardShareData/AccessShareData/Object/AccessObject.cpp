#include "../AccessShareData.hpp"
#include "../../../Config/Config.hpp"


namespace Kokoha
{
	Vec2 AccessObject::walk(Vec2 movement, const AccessShareData& shareData)
	{
		movement *= Scene::DeltaTime();
		Vec2 rtn = Vec2::Zero();

		if (shareData.getStageData().isWalkAble(m_body.center.movedBy(movement.x, 0)))
		{
			m_body.center.x += movement.x;
			rtn.x = movement.x;
		}

		if (shareData.getStageData().isWalkAble(m_body.center.movedBy(0, movement.y)))
		{
			m_body.center.y += movement.y;
			rtn.y = movement.y;
		}

		return rtn;
	}


	Vec2 AccessObject::walkToGoal(double speed, const Vec2& goal, const AccessShareData& shareData)
	{
		return (m_body.center - goal).length() < speed * Scene::DeltaTime()
			? Vec2::Zero()
			: walk(speed * shareData.getStageData().getPath(m_body.center, goal), shareData);
	}


	Vec2 AccessObject::walkToGoalThroughCenter(double speed, const Vec2& goal, const AccessShareData& shareData)
	{
		static const double WALK_CENTER_RATE = Config::get<double>(U"Board.Access.Object.walkCenter");

		if ((m_body.center - goal).length() < speed || !shareData.getStageData().isWalkAble(goal))
		{
			return Vec2::Zero();
		}

		Vec2 movement 
			= StageData::SQUARE_SIZE * shareData.getStageData().getPath(m_body.center, goal)
			+ (StageData::integerToPixel(StageData::pixelToInteger(m_body.center)) - m_body.center);

		if (movement.isZero()) { return Vec2::Zero(); }

		return walk(speed * movement.normalize(), shareData);
	}
}

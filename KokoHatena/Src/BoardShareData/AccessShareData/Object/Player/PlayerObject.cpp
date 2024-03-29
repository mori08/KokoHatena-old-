#include "PlayerObject.hpp"
#include "../../../../Config/Config.hpp"
#include "../../../../MyLibrary/MyLibrary.hpp"


namespace Kokoha
{

	PlayerObject::PlayerObject(const Vec2& pos)
		: AccessObject(Circle(pos, Config::get<double>(U"Board.Access.Object.Player.r")), AccessObjectType::PLAYER)
		, m_texture(U"Player", Config::get<Size>(U"Board.Access.Object.Player.textureSize"))
		, m_movement(Vec2::Zero())
		, m_goal(pos)
		, m_isChangingGoal(false)
	{
		static Animation ANIM = Config::get<Animation>(U"Board.Access.Object.Player.Anim");
		m_texture.setAnimation(U"Update", ANIM);
		m_texture.start(U"Update");
	}


	void PlayerObject::input(const Vec2& cursorPos)
	{
		// 移動量の決定
		static const double SPEED = Config::get<double>(U"Board.Access.Object.Player.speed");
		if (m_isChangingGoal ^= MouseL.down())
		{
			internalDividingPoint(m_goal, cursorPos, 1e-1);
		}
		if ((m_goal - m_body.center).length() > SPEED * Scene::DeltaTime())
		{
			m_movement = SPEED * Scene::DeltaTime() * (m_goal - m_body.center).normalized();
		}

		m_playerDirection.input(m_body.center, m_goal, m_isChangingGoal);
	}


	void PlayerObject::update(AccessShareData& shareData)
	{
		m_texture.update();

		walkPlayer(Vec2(m_movement.x, 0), shareData);
		walkPlayer(Vec2(0, m_movement.y), shareData);
		m_movement = Vec2::Zero();
		
		m_body.center += debugMovement();

		shareData.addLight(m_body.center, U"Board.Access.Object.Player.Light");

		m_playerDirection.update();
	}


	void PlayerObject::draw() const
	{
		m_texture.getTexture().drawAt(m_body.center);
		m_playerDirection.draw();
	}


	void PlayerObject::checkAnother(const AccessObject&)
	{

	}


	void PlayerObject::walkPlayer(const Vec2& movement, const AccessShareData& shareData)
	{
		bool isWalkAble = true;
		Vec2 next = m_body.center.movedBy(movement);
		for (auto pos : getRectNode(RectF(Arg::center(next), 2 * m_body.r)))
		{
			if (!shareData.getStageData().isWalkAble(pos)) { isWalkAble = false; }
		}
		if (isWalkAble) { m_body.center = next; }
	}

}

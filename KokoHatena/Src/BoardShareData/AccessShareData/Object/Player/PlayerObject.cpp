#include "PlayerObject.hpp"
#include "../../../../Config/Config.hpp"
#include "../../../../MyLibrary/MyLibrary.hpp"


namespace Kokoha
{

	PlayerObject::PlayerObject(const Vec2& pos)
		: AccessObject(Circle(pos, Config::get<double>(U"Board.Access.Object.Player.r")), AccessObjectType::PLAYER)
		, m_texture(U"Player", Config::get<Size>(U"Board.Access.Object.Player.textureSize"))
		, m_movement(Vec2::Zero())
		, m_direction(0,0)
	{
		static Animation ANIM = Config::get<Animation>(U"Board.Access.Object.Player.Anim");
		m_texture.setAnimation(U"Update", ANIM);
		m_texture.start(U"Update");
	}


	void PlayerObject::input(const Vec2& cursorPos)
	{
		static const double SPEED = Config::get<double>(U"Board.Access.Object.Player.speed");
		if ((cursorPos - m_body.center).length() > SPEED * Scene::DeltaTime())
		{
			m_movement = SPEED * Scene::DeltaTime() * (cursorPos - m_body.center).normalized();
		}

		static const double LIGHT_SPIN_SPEED = Config::get<double>(U"Board.Access.Object.Player.lightSpinSpeed");
		m_direction.second += Math::Pi * LIGHT_SPIN_SPEED * Mouse::Wheel();
	}


	void PlayerObject::update(AccessShareData& shareData)
	{
		static const double LIGHT_RADIUS
			= Config::get<double>(U"Board.Access.Object.Player.lightRadius");

		m_texture.update();

		walkPlayer(Vec2(m_movement.x, 0), shareData);
		walkPlayer(Vec2(0, m_movement.y), shareData);
		m_movement = Vec2::Zero();

		internalDividingPoint(m_direction.first, m_direction.second, 1e-1);
		
		shareData.addLight(Circle(m_body.center, LIGHT_RADIUS), m_direction.first, Math::QuarterPi);
	}


	void PlayerObject::draw() const
	{
		m_texture.getTexture().drawAt(m_body.center);
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

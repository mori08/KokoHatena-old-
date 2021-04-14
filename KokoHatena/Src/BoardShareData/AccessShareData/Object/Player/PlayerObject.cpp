#include "PlayerObject.hpp"
#include "../../../../Config/Config.hpp"


namespace Kokoha
{

	PlayerObject::PlayerObject(const Vec2& pos)
		: AccessObject(Circle(pos, Config::get<double>(U"Board.Access.Object.Player.r")), AccessObjectType::PLAYER)
		, m_texture(U"Player", Config::get<Size>(U"Board.Access.Object.Player.textureSize"))
	{
		static Animation ANIM = Config::get<Animation>(U"Board.Access.Object.Player.Anim");
		m_texture.setAnimation(U"Update", ANIM);
		m_texture.start(U"Update");
	}


	void PlayerObject::input(const Vec2& cursorPos)
	{
		static double SPEED = Config::get<double>(U"Board.Access.Object.Player.speed");
		if ((cursorPos - m_body.center).length() > SPEED * Scene::DeltaTime())
		{
			movement = SPEED * (cursorPos - m_body.center).normalized();
		}
	}


	void PlayerObject::update(AccessShareData& shareData)
	{
		m_texture.update();

		walk(movement, shareData);
		movement = Vec2::Zero();
	}


	void PlayerObject::draw() const
	{
		m_texture.getTexture().drawAt(m_body.center);
	}


	void PlayerObject::checkAnother(const AccessObject&)
	{

	}

}

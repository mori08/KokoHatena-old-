#pragma once


#include "../../AccessShareData.hpp"
#include "../../../../SliceTexture/SliceTexture.hpp"


namespace Kokoha
{
	/// <summary>
	/// PlayerObject�N���X
	/// AccessBoard�Ńv���C���[�����삷��I�u�W�F�N�g
	/// </summary>
	class PlayerObject : public AccessObject
	{
	private:

		// �摜
		SliceTexture m_texture;

		// �ړ���
		Vec2 m_movement;

		// ���̕���
		std::pair<double,double> m_direction;

	public:

		PlayerObject(const Vec2& pos);

	private:

		void input(const Vec2& cursorPos) override;

		void update(AccessShareData& shareData) override;

		void draw()const override;

		void checkAnother(const AccessObject&) override;

	private:

		void walkPlayer(const Vec2& movement, const AccessShareData& shareData);

	};
}
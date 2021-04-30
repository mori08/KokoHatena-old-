#pragma once


#include "../../AccessShareData.hpp"
#include "../../../../SliceTexture/SliceTexture.hpp"


namespace Kokoha
{
	/// <summary>
	/// PlayerObjectクラス
	/// AccessBoardでプレイヤーが操作するオブジェクト
	/// </summary>
	class PlayerObject : public AccessObject
	{
	private:

		// 画像
		SliceTexture m_texture;

		// 移動量
		Vec2 m_movement;

		// 移動の目的値
		Vec2 m_goal;

		// trueのとき目的値を変更, falseのときは目的値を固定
		bool m_isChangingGoal;

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
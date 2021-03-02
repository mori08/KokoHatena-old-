#pragma once


#include "../SecurityState.hpp"


namespace Kokoha
{
	/// <summary>
	/// SecurityWaitStateクラス
	/// 待ち状態
	/// </summary>
	class SecurityWaitState : public SecurityState
	{
	public:

		void input() override;

		void update() override;

		void draw() const override;

	};
}
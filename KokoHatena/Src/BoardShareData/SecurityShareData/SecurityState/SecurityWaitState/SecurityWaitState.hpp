#pragma once


#include "../SecurityState.hpp"


namespace Kokoha
{
	/// <summary>
	/// SecurityWaitStateƒNƒ‰ƒX
	/// ‘Ò‚¿ó‘Ô
	/// </summary>
	class SecurityWaitState : public SecurityState
	{
	public:

		void input(Optional<Vec2> mouseUpPos) override;

		void update() override;

		void draw() const override;

	};
}
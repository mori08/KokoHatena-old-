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

		void input() override;

		void update() override;

		void draw() const override;

	};
}
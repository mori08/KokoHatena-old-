#pragma once


#include "../SecurityState.hpp"


namespace Kokoha
{
	class SecurityWaitState : public SecurityState
	{
	public:

		void update() override;

		void draw() const override;

	};
}
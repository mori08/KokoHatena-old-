#pragma once


#include "../SecurityState.hpp"


namespace Kokoha
{
	/// <summary>
	/// SecurityWaitState�N���X
	/// �҂����
	/// </summary>
	class SecurityWaitState : public SecurityState
	{
	public:

		void input() override;

		void update() override;

		void draw() const override;

	};
}
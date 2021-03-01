#pragma once


namespace Kokoha
{
	class SecurityState
	{
	public:

		virtual ~SecurityState() {};

		virtual void update() = 0;

		virtual void draw()const = 0;

	};
}
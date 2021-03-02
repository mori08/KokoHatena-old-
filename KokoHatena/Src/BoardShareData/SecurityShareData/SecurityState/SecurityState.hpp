#pragma once


namespace Kokoha
{
	/// <summary>
	/// SecurityState�N���X
	/// SecurityBoard�̏��
	/// </summary>
	class SecurityState
	{
	public:

		virtual ~SecurityState() {};

		virtual void input() = 0;

		virtual void update() = 0;

		virtual void draw()const = 0;

	};
}
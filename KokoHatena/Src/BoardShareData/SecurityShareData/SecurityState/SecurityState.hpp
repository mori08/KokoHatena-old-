#pragma once


namespace Kokoha
{
	/// <summary>
	/// SecurityStateクラス
	/// SecurityBoardの状態
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
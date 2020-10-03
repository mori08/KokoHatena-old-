#pragma once


#include "../Board.hpp"


namespace Kokoha
{

	/// <summary>
	/// TestBoardクラス
	/// Boardクラスの入力・更新・描画のテスト
	/// </summary>
	class TestBoard : public Board
	{
	private:

		int32 m_number;

	public:

		TestBoard(const Role& role, int32 num);

	public:

		void inputInBoard() override;

		void updateInBoard() override;

		void drawInBoard() const override;

	};


	class Test1Board : public TestBoard
	{
	public:
		Test1Board()
			: TestBoard(Role::TEST1, 1)
		{
		}
	};
	class Test2Board : public TestBoard
	{
	public:
		Test2Board()
			: TestBoard(Role::TEST2, 2)
		{
		}
	};

}
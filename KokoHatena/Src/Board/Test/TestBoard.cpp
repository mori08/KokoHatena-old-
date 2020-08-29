#include "TestBoard.hpp"


namespace
{
	// ボードのサイズ
	constexpr Size BOARD_SIZE(640, 480);
}


namespace Kokoha
{

	TestBoard::TestBoard()
		: Board(Role::TEST, U"Test", BOARD_SIZE)
	{
	}


	void TestBoard::inputInBoard()
	{
	}


	void TestBoard::updateInBoard()
	{
	}


	void TestBoard::drawInBoard() const
	{
	}

}
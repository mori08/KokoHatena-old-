#include "TestBoard.hpp"


namespace
{
	// ボードのサイズ
	constexpr Size BOARD_SIZE(640, 480);
}


namespace Kokoha
{

	TestBoard::TestBoard(const Role& role, int32 num)
		: Board(role, U"Test", BOARD_SIZE)
	{
		m_number = num;
	}


	void TestBoard::inputInBoard()
	{
	}


	void TestBoard::updateInBoard()
	{
		
	}


	void TestBoard::drawInBoard() const
	{
		FontAsset(U"30")(ToString(m_number)).draw(40, 40);
	}

}
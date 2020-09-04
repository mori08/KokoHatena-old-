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
		m_circleCenter = Cursor::Pos();
	}


	void TestBoard::drawInBoard() const
	{
		Circle(0, 0, 100).draw(Palette::Red);
		Circle(m_circleCenter, 100).draw(Palette::Blue);
	}

}
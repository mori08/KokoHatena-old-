#include "TestBoard.hpp"


namespace
{
	// ボードのサイズ
	constexpr Size BOARD_SIZE(640, 480);
}


namespace Kokoha
{

	TestBoard::TestBoard(const Role& role)
		: Board(role, U"Test", BOARD_SIZE)
		, m_text(U"")
	{
	}


	void TestBoard::inputInBoard()
	{
		TextInput::UpdateText(m_text);
	}


	void TestBoard::updateInBoard()
	{
	}


	void TestBoard::drawInBoard() const
	{
		FontAsset(U"30")(m_text).draw(20, 40);
	}

}
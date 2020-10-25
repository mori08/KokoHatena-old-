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


	void TestBoard::inputInBoard(BoardShareData& shareData)
	{
		TextInput::UpdateText(m_text);
		
		if (KeyEnter.down()) { shareData.set(m_text); }
	}


	void TestBoard::updateInBoard(BoardShareData&)
	{

	}


	void TestBoard::drawInBoard(const BoardShareData& shareData) const
	{
		FontAsset(U"30")(m_text + shareData.get()).draw(20, 40);
	}

}
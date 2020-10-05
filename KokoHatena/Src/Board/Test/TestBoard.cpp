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
		m_time = 0;
	}


	void TestBoard::inputInBoard()
	{
		m_inputFlag = -1;
	}


	void TestBoard::updateInBoard()
	{
		m_time += Scene::DeltaTime();
		++m_inputFlag;
	}


	void TestBoard::drawInBoard() const
	{
		FontAsset(U"30")(ToString(m_number)).draw(40, 40);
		if (!m_inputFlag)
		{
			FontAsset(U"30")(ToString(int32(m_time))).draw(40, 80);
		}
	}

}
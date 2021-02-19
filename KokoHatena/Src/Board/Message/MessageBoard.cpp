#include "MessageBoard.hpp"


namespace
{
	// ボードのサイズ
	constexpr Size BOARD_SIZE(200, 350);
}


namespace Kokoha
{

	MessageBoard::MessageBoard(const Role& role)
		: Board(role, U"Message", BOARD_SIZE)
	{
	}


	void MessageBoard::inputInBoard(BoardShareData&)
	{
	}


	void MessageBoard::updateInBoard(BoardShareData&)
	{
	}


	void MessageBoard::drawInBoard(const BoardShareData&) const
	{
	}

}
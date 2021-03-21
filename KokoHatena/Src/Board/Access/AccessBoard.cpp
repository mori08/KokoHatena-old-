#include "AccessBoard.hpp"
#include "../../Config/Config.hpp"

namespace Kokoha
{
	AccessBoard::AccessBoard(const Role& role)
		: Board(role, U"Access", Config::get<Size>(U"Board.Access.size"))
	{
	}


	void AccessBoard::inputInBoard(BoardShareData&)
	{
	}


	void AccessBoard::updateInBoard(BoardShareData& shareData)
	{
		shareData.m_accessData.update();
	}


	void AccessBoard::drawInBoard(const BoardShareData& shareData) const
	{
		shareData.m_accessData.draw();
	}
}

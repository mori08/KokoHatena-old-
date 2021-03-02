#include "SecurityBoard.hpp"
#include "../../BoardShareData/BoardShareData.hpp"
#include "../../Config/Config.hpp"


namespace Kokoha
{
	SecurityBoard::SecurityBoard(const Role& role)
		: Board(role, U"Security", Config::get<Size>(U"Board.Security.size"))
	{
	}


	void SecurityBoard::inputInBoard(BoardShareData& shareData)
	{
		shareData.m_securityData.stateInput();
	}


	void SecurityBoard::updateInBoard(BoardShareData& shareData)
	{
		shareData.m_securityData.stateUpdate();
	}


	void SecurityBoard::drawInBoard(const BoardShareData& shareData) const
	{
		shareData.m_securityData.stateDraw();
	}
}
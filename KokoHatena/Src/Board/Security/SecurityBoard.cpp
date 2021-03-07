#include "SecurityBoard.hpp"
#include "../../BoardShareData/BoardShareData.hpp"
#include "../../Config/Config.hpp"
#include "../../RecordManager/RecordManager.hpp"


namespace Kokoha
{
	SecurityBoard::SecurityBoard(const Role& role)
		: Board(role, U"Security", Config::get<Size>(U"Board.Security.size"))
	{
		
	}


	SecurityBoard::~SecurityBoard()
	{
		
	}


	void SecurityBoard::inputInBoard(BoardShareData& shareData)
	{
		m_state.input();
	}


	void SecurityBoard::updateInBoard(BoardShareData& shareData)
	{
		m_state.update();
	}


	void SecurityBoard::drawInBoard(const BoardShareData& shareData) const
	{
		m_state.draw();
	}
}
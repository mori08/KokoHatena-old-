#include "SecurityBoard.hpp"
#include "../../BoardShareData/BoardShareData.hpp"
#include "../../Config/Config.hpp"
#include "../../RecordManager/RecordManager.hpp"
#include "../../BoardShareData/SecurityShareData/SecurityState/SecurityWaitState/SecurityWaitState.hpp"


namespace Kokoha
{
	SecurityBoard::SecurityBoard(const Role& role)
		: Board(role, U"Security", Config::get<Size>(U"Board.Security.size"))
	{
	}


	SecurityBoard::~SecurityBoard()
	{
		m_state->closeProcess();
	}


	void SecurityBoard::inputInBoard(BoardShareData& shareData)
	{
		if (!m_state)
		{
			m_state = std::make_unique<SecurityWaitState>();
		}

		if (auto nextStateFunc = shareData.m_securityData.getNextStateFunc())
		{
			m_state = std::move((nextStateFunc.value())());
		}

		Optional<Vec2> mouseUpPos = none;
		if (mouseLeftDown()) { mouseUpPos = cursorPosFInBoard(); }
		m_state->input(mouseUpPos);
	}


	void SecurityBoard::updateInBoard(BoardShareData&)
	{
		if (!m_state) { return; }

		m_state->update(cursorPosFInBoard());
	}


	void SecurityBoard::drawInBoard(const BoardShareData&) const
	{
		if (!m_state) { return; }

		m_state->draw();
	}
}
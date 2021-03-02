#include "BoardShareData.hpp"


namespace Kokoha
{
	BoardShareData::BoardShareData()
	{
		
	}


	void BoardShareData::addBoardStateChange(Board::Role role, BoardStateChange stateChange)
	{
		m_boardStateChangeList.emplace_back(role, stateChange);
	}


	Optional<std::pair<Board::Role, BoardShareData::BoardStateChange>> BoardShareData::getBoardStateChange()
	{
		if (m_boardStateChangeList.empty()) { return none; }
		
		auto rtn = m_boardStateChangeList.front();
		m_boardStateChangeList.pop_front();
		return rtn;
	}
}

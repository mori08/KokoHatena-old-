#include "SecurityShareData.hpp"
#include "SecurityState/SecurityWaitState/SecurityWaitState.hpp"


namespace Kokoha
{
	SecurityShareData::SecurityShareData()
	{
		m_makeStateMap[StateName::WAIT] = []() { return std::make_unique<SecurityWaitState>(); };

		m_boardState = m_makeStateMap[StateName::WAIT]();
	}
}

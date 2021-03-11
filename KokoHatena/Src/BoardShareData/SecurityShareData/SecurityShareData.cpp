#include "SecurityShareData.hpp"
#include "SecurityState/SecurityWaitState/SecurityWaitState.hpp"
#include "SecurityState/SecuritySelectState/SecuritySelectState.hpp"


namespace Kokoha
{
	SecurityShareData::SecurityShareData()
		: m_nextStateFunc(none)
		, m_changeAbleState(true)
	{
		m_makeStateMap[StateName::WAIT] = []() { return std::make_unique<SecurityWaitState>(); };
		m_makeStateMap[StateName::SELECT_ACCESS] = []()
		{
			return std::make_unique<SecuritySelectState>
				(
					U"Access.exe���_�E�����[�h���܂����H",
					[]() {  },
					[]() {  },
					[](){}
				);
		};
	}

	
	Optional<std::function<SecurityShareData::SecurityStatePtr()>> SecurityShareData::getNextStateFunc()
	{
		auto rtn = m_nextStateFunc;
		m_nextStateFunc = none;
		return rtn;
	}
}

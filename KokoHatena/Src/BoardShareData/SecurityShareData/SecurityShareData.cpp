#include "SecurityShareData.hpp"
#include "SecurityState/SecurityWaitState/SecurityWaitState.hpp"
#include "SecurityState/SecurityTextState/SecurityTextState.hpp"
#include "SecurityState/SecuritySelectState/SecuritySelectState.hpp"


namespace Kokoha
{
	SecurityShareData::SecurityShareData()
		: m_nextStateFunc(none)
		, m_changeAbleState(true)
	{
		m_makeStateMap[StateName::WAIT] = []() { return std::make_unique<SecurityWaitState>(); };
		m_makeStateMap[StateName::SELECT_ACCESS] = [this]()
		{
			return std::make_unique<SecuritySelectState>
				(
					U"Access.exe���_�E�����[�h���܂����H",
					[]() {  }, // TODO Loading��Ԃֈڍs
					[this]() { m_changeAbleState = true;  m_nextStateFunc = m_makeStateMap[StateName::CANCEL_DOWNLOAD]; },
					[this]() { m_changeAbleState = true; }
				);
		};
		m_makeStateMap[StateName::CANCEL_DOWNLOAD] =
			[]() { return std::make_unique<SecurityTextState>(U"�_�E�����[�h���L�����Z�����܂����D"); };
	}

	
	Optional<std::function<SecurityShareData::SecurityStatePtr()>> SecurityShareData::getNextStateFunc()
	{
		auto rtn = m_nextStateFunc;
		m_nextStateFunc = none;
		return rtn;
	}
}

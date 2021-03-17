#include "SecurityShareData.hpp"
#include "SecurityState/SecurityWaitState/SecurityWaitState.hpp"
#include "SecurityState/SecurityTextState/SecurityTextState.hpp"
#include "SecurityState/SecuritySelectState/SecuritySelectState.hpp"
#include "SecurityState/SecurityLoadState/SecurityLoadState.hpp"


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
					U"Access.exeをダウンロードしますか？",
					[this]() { m_nextStateFunc = m_makeStateMap[StateName::DOWNLOAD_ACCESS]; },
					[this]() { m_changeAbleState = true;  m_nextStateFunc = m_makeStateMap[StateName::CANCEL_DOWNLOAD]; },
					[this]() { m_changeAbleState = true; }
				);
		};
		m_makeStateMap[StateName::DOWNLOAD_ACCESS] = [this]() 
		{ 
			return std::make_unique<SecurityLoadState>
				(
					U"TestLoad",
					[this]() { m_changeAbleState = true; m_nextStateFunc = m_makeStateMap[StateName::COMPLETE_DOWNLOAD]; },
					[this]() { m_changeAbleState = true; }
				); 
		};
		m_makeStateMap[StateName::CANCEL_DOWNLOAD] =
			[]() { return std::make_unique<SecurityTextState>(U"ダウンロードをキャンセルしました．"); };
		m_makeStateMap[StateName::COMPLETE_DOWNLOAD] = 
			[]() { return std::make_unique<SecurityTextState>(U"ダウンロードが完了しました．"); };
	}

	
	Optional<std::function<SecurityShareData::SecurityStatePtr()>> SecurityShareData::getNextStateFunc()
	{
		auto rtn = m_nextStateFunc;
		m_nextStateFunc = none;
		return rtn;
	}
}

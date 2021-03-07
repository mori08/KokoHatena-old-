#pragma once


#include "SecurityState/SecurityState.hpp"
#include <Siv3D.hpp>


namespace Kokoha
{
	class SecurityShareData
	{
	public:

		using SecurityStatePtr = std::unique_ptr<SecurityState>;

		enum class StateName
		{
			WAIT
		};

	private:

		// ボードを作成する関数
		std::unordered_map<StateName, std::function<SecurityStatePtr()>> m_makeStateMap;

		// 次の状態
		Optional<std::function<SecurityStatePtr()>> m_nextStateFunc;

	public:
		
		SecurityShareData();

	public:

		/// <summary>
		/// 状態の切り替え
		/// </summary>
		/// <param name="state"> 切り替え先の状態 </param>
		void setState(const StateName& stateName)
		{
			m_nextStateFunc = m_makeStateMap[stateName];
		}

		/// <summary>
		/// 次の状態の取得
		/// </summary>
		/// <returns> 次の状態 </returns>
		Optional<std::function<SecurityStatePtr()>> getNextStateFunc();

	};
}
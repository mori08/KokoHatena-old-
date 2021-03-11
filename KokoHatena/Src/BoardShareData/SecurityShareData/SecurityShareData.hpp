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
			WAIT,
			SELECT_ACCESS
		};

	private:

		// ボードを作成する関数
		std::unordered_map<StateName, std::function<SecurityStatePtr()>> m_makeStateMap;

		// 次の状態
		Optional<std::function<SecurityStatePtr()>> m_nextStateFunc;

		// 状態の固定(外部ボードからの)
		bool m_changeAbleState;

	public:
		
		SecurityShareData();

	public:

		/// <summary>
		/// 状態の切り替え
		/// </summary>
		/// <param name="state"> 切り替え先の状態 </param>
		void setState(const StateName& stateName)
		{
			if (!m_changeAbleState) { return; }
			m_nextStateFunc = m_makeStateMap[stateName];
		}

		/// <summary>
		/// 次の状態の取得
		/// </summary>
		/// <returns> 次の状態 </returns>
		Optional<std::function<SecurityStatePtr()>> getNextStateFunc();

		/// <summary>
		/// 外部からの状態遷移をロック
		/// </summary>
		void lockState()
		{
			m_changeAbleState = false;
		}

		/// <summary>
		/// 状態を変更可能か
		/// </summary>
		/// <returns> 可能なとき true, そうでないとき false </returns>
		bool changeAbleState() const
		{
			return m_changeAbleState;
		}

	};
}
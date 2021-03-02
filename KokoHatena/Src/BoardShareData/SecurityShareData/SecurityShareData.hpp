#pragma once


#include "SecurityState/SecurityState.hpp"
#include <memory>
#include <unordered_map>
#include <functional>


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

		// SecurityBoardの状態
		std::unique_ptr<SecurityState> m_boardState;

		// ボードを作成する関数
		std::unordered_map<StateName, std::function<SecurityStatePtr()>> m_makeStateMap;

	public:
		
		SecurityShareData();

	public:

		/// <summary>
		/// 状態の切り替え
		/// </summary>
		/// <param name="state"> 切り替え先の状態 </param>
		void setState(const StateName& stateName)
		{
			m_boardState = m_makeStateMap[stateName]();
		}

		/// <summary>
		/// 状態に応じた入力
		/// </summary>
		void stateInput()
		{
			m_boardState->input();
		}

		/// <summary>
		/// 状態に応じた更新
		/// </summary>
		void stateUpdate()
		{
			m_boardState->update();
		}

		/// <summary>
		/// 状態に応じた描画
		/// </summary>
		void stateDraw() const
		{
			m_boardState->draw();
		}

	};
}
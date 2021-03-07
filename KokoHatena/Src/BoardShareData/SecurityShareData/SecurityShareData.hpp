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

		// ƒ{[ƒh‚ğì¬‚·‚éŠÖ”
		std::unordered_map<StateName, std::function<SecurityStatePtr()>> m_makeStateMap;

		// Ÿ‚Ìó‘Ô
		Optional<std::function<SecurityStatePtr()>> m_nextStateFunc;

	public:
		
		SecurityShareData();

	public:

		/// <summary>
		/// ó‘Ô‚ÌØ‚è‘Ö‚¦
		/// </summary>
		/// <param name="state"> Ø‚è‘Ö‚¦æ‚Ìó‘Ô </param>
		void setState(const StateName& stateName)
		{
			m_nextStateFunc = m_makeStateMap[stateName];
		}

		/// <summary>
		/// Ÿ‚Ìó‘Ô‚Ìæ“¾
		/// </summary>
		/// <returns> Ÿ‚Ìó‘Ô </returns>
		Optional<std::function<SecurityStatePtr()>> getNextStateFunc();

	};
}
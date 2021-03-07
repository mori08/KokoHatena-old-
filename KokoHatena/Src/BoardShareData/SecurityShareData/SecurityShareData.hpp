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

		// �{�[�h���쐬����֐�
		std::unordered_map<StateName, std::function<SecurityStatePtr()>> m_makeStateMap;

		// ���̏��
		Optional<std::function<SecurityStatePtr()>> m_nextStateFunc;

	public:
		
		SecurityShareData();

	public:

		/// <summary>
		/// ��Ԃ̐؂�ւ�
		/// </summary>
		/// <param name="state"> �؂�ւ���̏�� </param>
		void setState(const StateName& stateName)
		{
			m_nextStateFunc = m_makeStateMap[stateName];
		}

		/// <summary>
		/// ���̏�Ԃ̎擾
		/// </summary>
		/// <returns> ���̏�� </returns>
		Optional<std::function<SecurityStatePtr()>> getNextStateFunc();

	};
}
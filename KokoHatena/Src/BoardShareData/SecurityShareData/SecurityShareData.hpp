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

		// �{�[�h���쐬����֐�
		std::unordered_map<StateName, std::function<SecurityStatePtr()>> m_makeStateMap;

		// ���̏��
		Optional<std::function<SecurityStatePtr()>> m_nextStateFunc;

		// ��Ԃ̌Œ�(�O���{�[�h�����)
		bool m_changeAbleState;

	public:
		
		SecurityShareData();

	public:

		/// <summary>
		/// ��Ԃ̐؂�ւ�
		/// </summary>
		/// <param name="state"> �؂�ւ���̏�� </param>
		void setState(const StateName& stateName)
		{
			if (!m_changeAbleState) { return; }
			m_nextStateFunc = m_makeStateMap[stateName];
		}

		/// <summary>
		/// ���̏�Ԃ̎擾
		/// </summary>
		/// <returns> ���̏�� </returns>
		Optional<std::function<SecurityStatePtr()>> getNextStateFunc();

		/// <summary>
		/// �O������̏�ԑJ�ڂ����b�N
		/// </summary>
		void lockState()
		{
			m_changeAbleState = false;
		}

		/// <summary>
		/// ��Ԃ�ύX�\��
		/// </summary>
		/// <returns> �\�ȂƂ� true, �����łȂ��Ƃ� false </returns>
		bool changeAbleState() const
		{
			return m_changeAbleState;
		}

	};
}
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

		// SecurityBoard�̏��
		std::unique_ptr<SecurityState> m_boardState;

		// �{�[�h���쐬����֐�
		std::unordered_map<StateName, std::function<SecurityStatePtr()>> m_makeStateMap;

	public:
		
		SecurityShareData();

	public:

		/// <summary>
		/// ��Ԃ̐؂�ւ�
		/// </summary>
		/// <param name="state"> �؂�ւ���̏�� </param>
		void setState(const StateName& stateName)
		{
			m_boardState = m_makeStateMap[stateName]();
		}

		/// <summary>
		/// ��Ԃɉ���������
		/// </summary>
		void stateInput()
		{
			m_boardState->input();
		}

		/// <summary>
		/// ��Ԃɉ������X�V
		/// </summary>
		void stateUpdate()
		{
			m_boardState->update();
		}

		/// <summary>
		/// ��Ԃɉ������`��
		/// </summary>
		void stateDraw() const
		{
			m_boardState->draw();
		}

	};
}
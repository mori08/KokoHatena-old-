#pragma once


#include<Siv3D.hpp>
#include "../Board/Board.hpp"
#include"SecurityShareData/SecurityShareData.hpp"
#include"AccessShareData/AccessShareData.hpp"


namespace Kokoha
{
	/// <summary>
	/// BoardShareData�N���X
	/// Board�Ԃŋ��L����f�[�^
	/// BoardScene�֖��߂��s��
	/// </summary>
	class BoardShareData
	{
	public:

		enum class BoardStateChange
		{
			OPEN, // �J��,�őO�ʂɎ����Ă���
			CLOSE // ����
		};

	private:

		// �{�[�h�̏�ԕύX�ɂ��Ẵ��X�g
		std::list<std::pair<Board::Role, BoardStateChange>> m_boardStateChangeList;

	public:

		// SecurityBoard�̏�ԂɊւ��鋤�L�f�[�^
		SecurityShareData m_securityData;

		// AccessBoard�̏�ԂɊւ��鋤�L�f�[�^
		AccessShareData m_accessData;

	public:

		BoardShareData();

	public:

		/// <summary>
		/// �{�[�h�̏�ԕύX�����X�g�ɒǉ�
		/// </summary>
		/// <param name="role"> �{�[�h�̎�� </param>
		/// <param name="stateChange"> �ύX���e </param>
		void addBoardStateChange(Board::Role role, BoardStateChange stateChange);

		/// <summary>
		/// �{�[�h�̏�ԕύX���擾
		/// </summary>
		/// <returns> �{�[�h�̏�ԕύX, �����ꍇ none </returns>
		Optional<std::pair<Board::Role, BoardStateChange>> getBoardStateChange();

	};
}
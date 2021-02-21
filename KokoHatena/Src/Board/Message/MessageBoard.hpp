#pragma once


#include "../Board.hpp"


namespace Kokoha
{
	/// <summary>
	/// MessageBoard�N���X
	/// Message�̕\��
	/// </summary>
	class MessageBoard : public Board
	{
	private:

		// �\�����郁�b�Z�[�W�̖��O
		Optional<String> m_messageName;

		// ���b�Z�[�W�p�̐ݒ�t�@�C��
		const TOMLReader m_toml;

	public:

		MessageBoard(const Role& role);

	public:

		void inputInBoard(BoardShareData& shareData) override;

		void updateInBoard(BoardShareData& shareData) override;

		void drawInBoard(const BoardShareData& shareData) const override;

	};
}
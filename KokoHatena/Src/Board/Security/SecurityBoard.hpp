#pragma once

#include "../Board.hpp"

namespace Kokoha
{
	/// <summary>
	/// SecurityBoard�N���X
	/// �V�X�e���Ɋւ���Ă����ȃ{�[�h
	/// </summary>
	class SecurityBoard : public Board
	{
	private:

	public:

		SecurityBoard(const Role& role);
		~SecurityBoard();

	public:

		void inputInBoard(BoardShareData& shareData) override;

		void updateInBoard(BoardShareData& shareData) override;

		void drawInBoard(const BoardShareData& shareData) const override;

	};
}
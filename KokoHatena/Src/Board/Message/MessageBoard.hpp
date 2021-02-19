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

	public:

		MessageBoard(const Role& role);

	public:

		void inputInBoard(BoardShareData& shareData) override;

		void updateInBoard(BoardShareData& shareData) override;

		void drawInBoard(const BoardShareData& shareData) const override;

	};
}
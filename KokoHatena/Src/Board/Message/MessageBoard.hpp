#pragma once


#include "../Board.hpp"


namespace Kokoha
{
	/// <summary>
	/// MessageBoardƒNƒ‰ƒX
	/// Message‚Ì•\Ž¦
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
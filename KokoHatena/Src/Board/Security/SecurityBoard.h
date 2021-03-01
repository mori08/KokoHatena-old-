#pragma once

#include "../Board.hpp"

namespace Kokoha
{
	class SecurityBoard : public Board
	{
	private:

	public:

		SecurityBoard(const Role& role);

	public:

		void inputInBoard(BoardShareData& shareData) override;

		void updateInBoard(BoardShareData& shareData) override;

		void drawInBoard(const BoardShareData& shareData) const override;

	};
}
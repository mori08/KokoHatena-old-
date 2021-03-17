#pragma once


#include "../../BoardShareData/BoardShareData.hpp"


namespace Kokoha
{
	class AccessBoard : public Board
	{
	private:

	public:

		AccessBoard(const Role& role);

	private:

		void inputInBoard(BoardShareData& shareData) override;

		void updateInBoard(BoardShareData& shareData) override;

		void drawInBoard(const BoardShareData& shareData) const override;

	};
}
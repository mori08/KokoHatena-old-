#pragma once

#include "../Board.hpp"
#include "../../BoardShareData/SecurityShareData/SecurityState/SecurityState.hpp"

namespace Kokoha
{
	/// <summary>
	/// SecurityBoardクラス
	/// システムに関わってそうなボード
	/// </summary>
	class SecurityBoard : public Board
	{
	private:

		// 状態
		SecurityState m_state;

	public:

		SecurityBoard(const Role& role);
		~SecurityBoard();

	public:

		void inputInBoard(BoardShareData& shareData) override;

		void updateInBoard(BoardShareData& shareData) override;

		void drawInBoard(const BoardShareData& shareData) const override;

	};
}
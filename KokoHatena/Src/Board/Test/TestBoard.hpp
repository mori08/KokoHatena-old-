#pragma once


#include "../Board.hpp"


namespace Kokoha
{

	/// <summary>
	/// TestBoardクラス
	/// Boardクラスの入力・更新・描画のテスト
	/// </summary>
	class TestBoard : public Board
	{
	private:

		String m_text;

	public:

		TestBoard(const Role& role);

	public:

		void inputInBoard(BoardShareData& shareData) override;

		void updateInBoard(BoardShareData& shareData) override;

		void drawInBoard(const BoardShareData& shareData) const override;

	};

}
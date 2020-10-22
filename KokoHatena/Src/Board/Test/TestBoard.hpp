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

		void inputInBoard() override;

		void updateInBoard() override;

		void drawInBoard() const override;

	};

}
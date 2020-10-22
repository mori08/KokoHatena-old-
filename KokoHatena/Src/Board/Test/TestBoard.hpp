#pragma once


#include "../Board.hpp"


namespace Kokoha
{

	/// <summary>
	/// TestBoard�N���X
	/// Board�N���X�̓��́E�X�V�E�`��̃e�X�g
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
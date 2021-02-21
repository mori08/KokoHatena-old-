#pragma once


#include "../Board.hpp"


namespace Kokoha
{
	/// <summary>
	/// MessageBoardクラス
	/// Messageの表示
	/// </summary>
	class MessageBoard : public Board
	{
	private:

		// 表示するメッセージの名前
		Optional<String> m_messageName;

		// メッセージ用の設定ファイル
		const TOMLReader m_toml;

	public:

		MessageBoard(const Role& role);

	public:

		void inputInBoard(BoardShareData& shareData) override;

		void updateInBoard(BoardShareData& shareData) override;

		void drawInBoard(const BoardShareData& shareData) const override;

	};
}
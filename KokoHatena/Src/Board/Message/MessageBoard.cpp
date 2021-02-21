#include "MessageBoard.hpp"
#include "../../Config/Config.hpp"


namespace Kokoha
{

	MessageBoard::MessageBoard(const Role& role)
		: Board(role, U"Message", Config::get<Size>(U"Board.Message.size"))
		, m_toml(U"asset/data/message.toml")
	{

	}


	void MessageBoard::inputInBoard(BoardShareData&)
	{
	}


	void MessageBoard::updateInBoard(BoardShareData&)
	{
	}


	void MessageBoard::drawInBoard(const BoardShareData&) const
	{
		// 1つのメッセージに使う長方形のサイズ
		static const Point ONE_MESSAGE_SIZE = Config::get<Point>(U"Board.Message.oneMessageSize");
		// 送信者を表示する座標
		static const Point FROM_POS         = Config::get<Point>(U"Board.Message.fromPos");
		// 日付を表示する座標
		static const Point DATE_POS         = Config::get<Point>(U"Board.Message.datePos");
		// 件名を表示する座標
		static const Point TITLE_POS        = Config::get<Point>(U"Board.Message.titlePos");
		// 選択中のメッセージ背景の色
		static const ColorF SELECTED_MESSAGE_COLOR = Config::get<ColorF>(U"Board.Message.selectedMessageColor");

		// 基準座標
		Point pos = Point::Down(Config::get<int32>(U"Board.controlFrameHeight"));
		for (const auto& name : m_toml[U"Name.list"].arrayView())
		{
			Rect(pos, ONE_MESSAGE_SIZE).drawFrame(1, Palette::White);
			if (Rect(pos, ONE_MESSAGE_SIZE).contains(cursorPosInBoard()))
			{
				Rect(pos, ONE_MESSAGE_SIZE).draw(SELECTED_MESSAGE_COLOR);
			}

			FontAsset(U"15")(m_toml[name.getString() + U".from" ].getString()).draw(pos + FROM_POS);
			FontAsset(U"15")(m_toml[name.getString() + U".date" ].getString()).draw(pos + DATE_POS);
			FontAsset(U"15")(m_toml[name.getString() + U".title"].getString()).draw(pos + TITLE_POS);
			
			pos.y += ONE_MESSAGE_SIZE.y;
		}
	}

}
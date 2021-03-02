#include "MessageBoard.hpp"
#include "../../Config/Config.hpp"
#include "../../RecordManager/RecordManager.hpp"


namespace Kokoha
{

	MessageBoard::MessageBoard(const Role& role)
		: Board(role, U"Message", Config::get<Size>(U"Board.Message.size"))
		, m_toml(U"asset/data/message.toml")
	{

	}


	void MessageBoard::inputInBoard(BoardShareData&)
	{
		if (m_messageName)
		{
			updateReadMessage();
		}
		else
		{
			updateSelectMessage();
		}
	}


	void MessageBoard::updateInBoard(BoardShareData&)
	{
	}


	void MessageBoard::drawInBoard(const BoardShareData&) const
	{
		if (m_messageName)
		{
			drawReadMessage();
		}
		else
		{
			drawSelectMessage();
		}
	}


	void MessageBoard::updateSelectMessage()
	{
		// 1�̃��b�Z�[�W�Ɏg�������`�̃T�C�Y
		static const Point ONE_MESSAGE_SIZE = Config::get<Point>(U"Board.Message.Select.oneMessageSize");

		Point pos = Point::Down(Config::get<int32>(U"Board.controlFrameHeight"));
		for (const auto& name : m_toml[U"Name.list"].arrayView())
		{
			if (name.getString() == U"Robot" && !readAbleRobotMessage()) { break; }

			if (mouseLeftDown() && Rect(pos, ONE_MESSAGE_SIZE).contains(cursorPosInBoard()))
			{
				m_messageName = name.getString();
				RecordManager::instance().setRecord(U"Message" + name.getString(), 1);
			}
			pos.y += ONE_MESSAGE_SIZE.y;
		}
	}


	void MessageBoard::drawSelectMessage() const
	{
		// 1�̃��b�Z�[�W�Ɏg�������`�̃T�C�Y
		static const Point ONE_MESSAGE_SIZE = Config::get<Point>(U"Board.Message.Select.oneMessageSize");
		// ���M�҂�\��������W
		static const Point FROM_POS = Config::get<Point>(U"Board.Message.Select.fromPos");
		// ���t��\��������W
		static const Point DATE_POS = Config::get<Point>(U"Board.Message.Select.datePos");
		// ������\��������W
		static const Point TITLE_POS = Config::get<Point>(U"Board.Message.Select.titlePos");
		// �I�𒆂̃��b�Z�[�W�w�i�̐F
		static const ColorF SELECTED_MESSAGE_COLOR = Config::get<ColorF>(U"Board.Message.Select.selectedMessageColor");

		// ����W
		Point pos = Point::Down(Config::get<int32>(U"Board.controlFrameHeight"));
		for (const auto& name : m_toml[U"Name.list"].arrayView())
		{
			if (name.getString() == U"Robot" && !readAbleRobotMessage()) { break; }

			if (Rect(pos, ONE_MESSAGE_SIZE).contains(cursorPosInBoard()))
			{
				Rect(pos, ONE_MESSAGE_SIZE).draw(SELECTED_MESSAGE_COLOR);
			}
			Rect(pos, ONE_MESSAGE_SIZE).drawFrame(1, Palette::White);

			FontAsset(U"14")(m_toml[name.getString() + U".from"].getString()).draw(pos + FROM_POS);
			FontAsset(U"12")(m_toml[name.getString() + U".date"].getString()).draw(pos + DATE_POS);
			FontAsset(U"15")(m_toml[name.getString() + U".title"].getString()).draw(pos + TITLE_POS);

			pos.y += ONE_MESSAGE_SIZE.y;
		}	
	}


	void MessageBoard::updateReadMessage()
	{
		static const Rect BACK_BOTTAN = Config::get<Rect>(U"Board.Message.Read.backBottan");
		if (mouseLeftDown() && BACK_BOTTAN.contains(cursorPosInBoard()))
		{
			m_messageName = none;
		}
	}


	void MessageBoard::drawReadMessage() const
	{
		// ���M�҂�\��������W
		static const Point FROM_POS  = Config::get<Point>(U"Board.Message.Read.fromPos");
		// ���t��\��������W
		static const Point DATE_POS  = Config::get<Point>(U"Board.Message.Read.datePos");
		// ������\��������W
		static const Point TITLE_POS = Config::get<Point>(U"Board.Message.Read.titlePos");
		// ������\��������W
		static const Point TEXT_POS  = Config::get<Point>(U"Board.Message.Read.textPos");
		// �����̏�̐�
		static const Rect LINE1 = Config::get<Rect>(U"Board.Message.Read.line1");
		// �����̉��̐�
		static const Rect LINE2 = Config::get<Rect>(U"Board.Message.Read.line2");
		// ���̐F
		static const ColorF LINE_COLOR = Config::get<ColorF>(U"Board.Message.Read.lineColor");
		// �߂�{�^��
		static const Rect BACK_BOTTAN = Config::get<Rect>(U"Board.Message.Read.backBottan");
		// �I�𒆂̃��b�Z�[�W�w�i�̐F
		static const ColorF SELECTED_COLOR = Config::get<ColorF>(U"Board.Message.Select.selectedMessageColor");

		FontAsset(U"14")(U"FROM: "+m_toml[m_messageName.value() + U".from" ].getString()).draw(FROM_POS);
		FontAsset(U"12")(m_toml[m_messageName.value() + U".date" ].getString()).draw(DATE_POS);
		FontAsset(U"15")(m_toml[m_messageName.value() + U".title"].getString()).draw(TITLE_POS);
		FontAsset(U"12")(m_toml[m_messageName.value() + U".text" ].getString()).draw(TEXT_POS);

		LINE1.draw(LINE_COLOR);
		LINE2.draw(LINE_COLOR);

		if (BACK_BOTTAN.contains(cursorPosInBoard()))
		{
			BACK_BOTTAN.draw(SELECTED_COLOR);
		}
		FontAsset(U"25")(U"��").drawAt(BACK_BOTTAN.center());
	}


	bool MessageBoard::readAbleRobotMessage()
	{
		return RecordManager::instance().getRecord(U"MessageDoctor") == 1
			&& RecordManager::instance().getRecord(U"MessageBoss")   == 1
			&& RecordManager::instance().getRecord(U"MessageFriend") == 1;
	}

}
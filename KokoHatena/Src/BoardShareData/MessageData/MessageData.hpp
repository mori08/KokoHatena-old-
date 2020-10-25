#pragma once


#include<Siv3D.hpp>


namespace Kokoha
{
	/// <summary>
	/// Messageクラス
	/// 話し手と話した内容をまとめたもの
	/// </summary>
	class Message
	{
	public:

		// 話し手, true のとき 自分, false のとき 相手
		const bool speaker;

		// 内容
		const String text;

		Message(bool a_speaker, String a_text)
			: speaker(a_speaker)
			, text(a_text)
		{
		}

	};

	
	/// <summary>
	/// MessageDataクラス
	/// メッセージ用のデータ
	/// </summary>
	class MessageData
	{
	private:

		// 履歴 [通話相手]=(メッセージのリスト)
		std::unordered_map<String, Array<Message>> m_history;

		// 会話のTOMLデータ
		const TOMLReader m_toml;

	public:

		MessageData();

	};
	
}
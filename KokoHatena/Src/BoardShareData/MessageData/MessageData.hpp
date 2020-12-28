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

		// 履歴 [会話相手]=(メッセージのリスト)
		std::unordered_map<String, Array<Message>> m_history;

		// 会話のTOMLデータ
		const TOMLReader m_toml;

	public:

		MessageData();

	public:

		/// <summary>
		/// メッセージの追加
		/// </summary>
		/// <param name="name"   > 会話相手の名前 </param>
		/// <param name="speaker"> 話し手, trueのとき 自分, falseのとき 相手 </param>
		/// <param name="text"   > 内容 </param>
		void addMessage(const String& name, bool speaker, const String& text)
		{
			m_history[name].emplace_back(speaker, text);
		}

		/// <summary>
		/// 会話履歴の取得
		/// </summary>
		/// <param name="name"> 会話相手 </param>
		/// <returns> 会話履歴 </returns>
		const Array<Message>& getHistory(const String& name)const;

	};
	
}
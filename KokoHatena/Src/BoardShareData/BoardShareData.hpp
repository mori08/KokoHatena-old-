#pragma once


#include<Siv3D.hpp>
#include"MessageData/MessageData.hpp"


namespace Kokoha
{
	/// <summary>
	/// BoardShareDataクラス
	/// Board間で共有するデータ
	/// BoardSceneへ命令も行う
	/// </summary>
	class BoardShareData
	{
	private:

		String m_text;

		// メッセージのデータ
		MessageData m_messageData;

	public:

		BoardShareData();

	public:

		void set(const String& text) { m_text = text; }
		const String& get() const { return m_text; }

	};
}
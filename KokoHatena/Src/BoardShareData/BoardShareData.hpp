#pragma once


#include<Siv3D.hpp>
#include"MessageData/MessageData.hpp"


namespace Kokoha
{
	/// <summary>
	/// BoardShareData�N���X
	/// Board�Ԃŋ��L����f�[�^
	/// BoardScene�֖��߂��s��
	/// </summary>
	class BoardShareData
	{
	private:

		String m_text;

		// ���b�Z�[�W�̃f�[�^
		MessageData m_messageData;

	public:

		BoardShareData();

	public:

		void set(const String& text) { m_text = text; }
		const String& get() const { return m_text; }

	};
}
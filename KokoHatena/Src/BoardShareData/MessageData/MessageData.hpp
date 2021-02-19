#pragma once


#include<Siv3D.hpp>


namespace Kokoha
{
	/// <summary>
	/// Message�N���X
	/// �b����Ƙb�������e���܂Ƃ߂�����
	/// </summary>
	class Message
	{
	public:

		// �b����, true �̂Ƃ� ����, false �̂Ƃ� ����
		const bool speaker;

		// ���e
		const String text;

		Message(bool a_speaker, String a_text)
			: speaker(a_speaker)
			, text(a_text)
		{
		}

	};

	
	/// <summary>
	/// MessageData�N���X
	/// ���b�Z�[�W�p�̃f�[�^
	/// </summary>
	class MessageData
	{
	private:

		// ���� [��b����]=(���b�Z�[�W�̃��X�g)
		std::unordered_map<String, Array<Message>> m_history;

		// ��b��TOML�f�[�^
		const TOMLReader m_toml;

	public:

		MessageData();

	public:

		/// <summary>
		/// ��b�����̎擾
		/// </summary>
		/// <param name="name"> ��b���� </param>
		/// <returns> ��b���� </returns>
		const Array<Message>& getHistory(const String& name)const;

	};
	
}
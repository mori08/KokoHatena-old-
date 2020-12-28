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
		/// ���b�Z�[�W�̒ǉ�
		/// </summary>
		/// <param name="name"   > ��b����̖��O </param>
		/// <param name="speaker"> �b����, true�̂Ƃ� ����, false�̂Ƃ� ���� </param>
		/// <param name="text"   > ���e </param>
		void addMessage(const String& name, bool speaker, const String& text)
		{
			m_history[name].emplace_back(speaker, text);
		}

		/// <summary>
		/// ��b�����̎擾
		/// </summary>
		/// <param name="name"> ��b���� </param>
		/// <returns> ��b���� </returns>
		const Array<Message>& getHistory(const String& name)const;

	};
	
}
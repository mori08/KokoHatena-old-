#pragma once


#include<Siv3D.hpp>


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

	public:

		BoardShareData();

	public:

		void set(const String& text) { m_text = text; }
		const String& get() const { return m_text; }

	};
}
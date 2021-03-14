#pragma once


#include "../SecurityState.hpp"


namespace Kokoha
{
	/*
	* SecutiryTextState�N���X
	* �w�肳�ꂽ�e�L�X�g��\��������
	*/
	class SecurityTextState : public SecurityState
	{
	private:

		// Board�ɕ\�����镶��
		const String m_text;

	public:

		SecurityTextState(const String& text);

	private:

		void input(Optional<Vec2>) override;

		void update(const Vec2&) override;

		void draw() const override;

	};
}
#pragma once


#include "../SecurityState.hpp"


namespace Kokoha
{
	/// <summary>
	/// SecurityLoadState�N���X
	/// �Q�[�W��\��������
	/// </summary>
	class SecurityLoadState : public SecurityState
	{
	private:

		// Board�ɕ\������e�L�X�g
		const String m_text;

		// �I����ɍs������
		const std::function<void()> m_finishFunc;

		// �r���ŃE�B���h�E�����ꂽ�Ƃ��̏���
		const std::function<void()> m_colseFunc;

	private:

		// �i����(0 -> 1)
		double m_progress;

	public:

		SecurityLoadState(const String& text, const std::function<void()>& finishFunc);

	private:

		void input(Optional<Vec2>) override;

		void update(const Vec2&) override;

		void draw() const override;

	};
}
#pragma once


#include <Siv3D.hpp>
#include "../SecurityState.hpp"


namespace Kokoha
{
	/// <summary>
	/// SecutitySelectState�N���X
	/// �I������I�΂��C���̑I���ɉ������������s��
	/// </summary>
	class SecuritySelectState : public SecurityState
	{
	private:

		// Board�ɕ\�����镶(�I����)
		const String m_text;

		// yes��I�񂾎��̏���
		const std::function<void()> m_yesFunc;

		// no��I�񂾎��̏���
		const std::function<void()> m_noFunc;

		// �J�[�\���̍��W
		Vec2 m_cursorPos;

	public:

		/// <summary>
		/// �I������I�΂�����
		/// </summary>
		/// <param name="text"> Board�ɕ\�����镶 </param>
		/// <param name="yesFunc"> yes��I�񂾎��̏��� </param>
		/// <param name="noFunc"> no��I�񂾎��̏��� </param>
		/// <param name="closeProcess"> �����Ƃ��̏��� </param>
		SecuritySelectState(const String& text, const std::function<void()>& yesFunc, const std::function<void()>& noFunc, const std::function<void()>& closeProcess);

	private:

		void input(Optional<Vec2>) override;

		void update(const Vec2& cursorPosInBoard) override;

		void draw() const override;

	private:

		const Rect& yesButton() const;

		const Rect& noButton() const;

	};
}
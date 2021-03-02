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

	public:

		/// <summary>
		/// �I������I�΂�����
		/// </summary>
		/// <param name="text"> Board�ɕ\�����镶 </param>
		/// <param name="yesFunc"> yes��I�񂾎��̏��� </param>
		/// <param name="noFunc"> no��I�񂾎��̏��� </param>
		SecuritySelectState(const String& text, std::function<void()> yesFunc, std::function<void()> noFunc);

	private:

		void input() override;

		void update() override;

		void draw() const override;

	};
}
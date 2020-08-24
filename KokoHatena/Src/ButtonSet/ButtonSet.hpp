#pragma once


#include "Button/Button.hpp"


namespace Kokoha
{
	/*
	* ButtonSet�N���X
	* Button�N���X�̃��X�g������
	* �X�V��폜���s��
	*/
	class ButtonSet
	{
	private:

		// �Ǘ����Ă���{�^���̘A�z�z��
		std::unordered_map<String, Button> m_buttonMap;

		// �I�𒆂̃{�^���̖��O
		String m_selectedButtonName;

	public:

		/// <summary>
		/// �{�^���̓o�^
		/// </summary>
		/// <param name="name"  > �{�^���̖��O </param>
		/// <param name="region"> �{�^���͈̔� </param>
		void registerButton(const String& name, const Rect& region);

		/// <summary>
		/// �{�^���̓o�^
		/// </summary>
		/// <param name="button"> �{�^�� </param>
		void registerButton(const Button& button);

		/// <summary>
		/// �I�𒆂̃{�^���̕ύX
		/// </summary>
		/// <param name="name"> �{�^���̖��O </param>
		void setSelectedButton(const String& name);

		/// <summary>
		/// �{�^�����������Ƃ��̏����̐ݒ�
		/// </summary>
		/// <param name="name">        �{�^���̖��O     </param>
		/// <param name="onClickFunc"> �������Ƃ��̏��� </param>
		void setOnClickFunc(const String& name, std::function<void()> onClickFunc);

		/// <summary>
		/// �I�𒆂̃{�^���̎擾
		/// </summary>
		/// <returns> �I�𒆂̃{�^�� </returns>
		const Button& getSelectedButton() const;

		/// <summary>
		/// �{�^���̍폜
		/// </summary>
		/// <param name="name"> �폜����{�^���̖��O </param>
		void eraseButton(const String& name);

		/// <summary>
		/// �{�^���̃��X�g����ɂ��܂�
		/// </summary>
		void clearButtonList();

		/// <summary>
		/// �{�^���̑I���y�у{�^���������ꂽ�Ƃ��̏����̌Ăяo��
		/// </summary>
		/// <param name="basePos"> ����W </param>
		/// <remarks>
		/// ���͂ɉ������{�^���I���̕ύX��
		/// ����L�[�������ꂽ�Ƃ����̃{�^����OnClick�֐����Ăт܂�
		/// 1�t���[����2�x�ȏ�g��Ȃ��ł��������B
		/// </remarks>
		void update(const Point& basePos = Point::Zero());

	};
}
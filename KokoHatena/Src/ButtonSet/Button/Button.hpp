#pragma once


#include<Siv3D.hpp>


namespace Kokoha
{
	/*
	* Button�N���X
	* {�{�^���͈̔�,���O,�������Ƃ��̏���}���܂Ƃ߂�.
	*/
	class Button
	{
	private:

		// ���O
		const String m_name;

		// �͈�
		Rect m_region;

		// �N���b�N���ꂽ�Ƃ��̏���
		std::function<void()> m_onClickFunc;

	public:

		/// <summary>
		/// �{�^��
		/// </summary>
		/// <param name="name"  > ���O </param>
		/// <param name="region"> �͈� </param>
		Button(const String& name, const Rect& region);

	public:

		/// <summary>
		/// �{�^���̖��O�̎擾
		/// </summary>
		/// <returns> �{�^���̖��O </returns>
		const String& getName() const
		{
			return m_name;
		}
		
		/// <summary>
		/// �͈͂̊���W�̕ύX
		/// </summary>
		/// <param name="pos"> �͈͂̊���W </param>
		void setPos(const Point& pos)
		{
			m_region.setPos(pos);
		}

		/// <summary>
		/// �͈͂̃T�C�Y�̕ύX
		/// </summary>
		/// <param name="pos"> �͈͂̊���W </param>
		void setSize(const Size& size)
		{
			m_region.setSize(size);
		}

		/// <summary>
		/// �{�^���͈̔͂̎擾
		/// </summary>
		/// <returns> �{�^���͈̔� </summary>
		const Rect& getRegion() const
		{
			return m_region;
		}

		/// <summary>
		/// �N���b�N�����Ƃ��̏����̐ݒ�
		/// </summary>
		/// <param name="onClickFunc"> �������Ƃ��̏��� </param>
		void setOnClickFunc(const std::function<void()>& onClickFunc)
		{
			m_onClickFunc = onClickFunc;
		}

		/// <summary>
		/// �N���b�N�����Ƃ��̏���
		/// </summary>
		void onClick() const
		{
			m_onClickFunc();
		}

	};
}
#pragma once


#include<Siv3D.hpp>


namespace Kokoha
{
	/// <summary>
	/// Board�N���X
	/// �{�[�h�̊��
	/// </summary>
	class Board
	{
	public:

		/// <summary>
		/// ���(����) ���ʗp�ɂ��g��
		/// </summary>
		enum class Role
		{
			MAIL // ���[��
		};

		/// <summary>
		/// ��Ԃ̐؂�ւ��ɂ��Ă̏o��
		/// </summary>
		enum class StateChange
		{
			CLOSE,    // ����
			MINIMIZE, // �ŏ���
			NONE      // �ύX�Ȃ�
		};

	private:

		// ���(����)
		const Role m_role;

		// ���O
		const String m_name;

		// �T�C�Y
		const Size m_size;

		// �E�B���h�E������̍��W
		Point m_pos;

	public:

		Board(Role role, const String& name, const Size& size);

	public:

		/// <summary>
		/// ���͂̎�t
		/// </summary>
		void input();

		/// <summary>
		/// �{�[�h���̓��͂̎�t
		/// </summary>
		virtual void inputInBoard() = 0;

		/// <summary>
		/// �X�V
		/// </summary>
		/// <returns> ��Ԃ̕ύX </returns>
		StateChange update();

		/// <summary>
		/// �{�[�h���̍X�V
		/// </summary>
		/// <remarks>
		/// �}�E�X��L�[�{�[�h�̓��͂��K�v�Ȃ��̂�
		/// input�֐��ōs��
		/// </remarks>
		virtual void updateInBoard() = 0;

		/// <summary>
		/// �`��
		/// </summary>
		void draw() const;

		/// <summary>
		/// �{�[�h���̕`��
		/// </summary>
		virtual void drawInBoard() const = 0;

	};

}
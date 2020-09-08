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
			TEST, // �e�X�g
			MAIL  // ���[��
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

		// ����̍��W
		Point m_pos;

		// ���
		StateChange m_state;

		// ���W�ړ����̊���W(none�̂Ƃ��ړ����Ȃ�)
		Optional<Point> m_optMovePos;

		// �s�����x
		double m_alpha;

		// ����{�^��
		const Rect m_closeButton;

		// �ŏ����{�^��
		const Rect m_minimizeButton;

		// �����_�[�e�N�X�`��(�{�[�h���̕`��)
		const MSRenderTexture m_render;

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

	protected:

		/// <summary>
		/// �{�[�h���̃}�E�X���W�̎擾
		/// </summary>
		/// <returns> �{�[�h���̃}�E�X���W </returns>
		Point cursorPosInBoard() const
		{
			return Cursor::Pos() - m_pos;
		}

		/// <summary>
		/// �{�[�h���̃}�E�X���W�̎擾
		/// </summary>
		/// <returns> �{�[�h���̃}�E�X���W </returns>
		Vec2 cursorPosFInBoard() const
		{
			return Cursor::PosF() - m_pos;
		}

	private:

		/// <summary>
		/// �s�����x�̕ύX
		/// </summary>
		/// <returns> �ύX���I�������Ƃ� true , �����łȂ��Ƃ� false </returns>
		bool changeAlpha();

		/// <summary>
		/// �J�[�\���ł̍��W�̈ړ�
		/// <\summary>
		void movePos();

	};

}
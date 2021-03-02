#pragma once


#include"../BoardSymbol/BoardSymbol.hpp"


namespace Kokoha
{
	class BoardShareData;

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
			TEST1,   // �e�X�g1
			TEST2,   // �e�X�g2
			MAIL,    // ���[��
			SECURITY // �Z�L�����e�B
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

		// ����t���[��
		const Rect m_controlFrame;

		// ����{�^��
		const Rect m_closeButton;

		// �ŏ����{�^��
		const Rect m_minimizeButton;

		// �����_�[�e�N�X�`��(�{�[�h���̕`��)
		const MSRenderTexture m_render;

		// ����̍��W
		Point m_pos;

		// �s�����x
		double m_alpha;

		// ���
		StateChange m_state;

		// ���W�ړ����̊���W(none�̂Ƃ��ړ����Ȃ�)
		Optional<Point> m_optMovePos;

	public:

		Board(Role role, const String& name, const Size& size);

		virtual ~Board() {}

	public:

		/// <summary>
		/// ���͂̎�t
		/// </summary>
		void input(BoardShareData& shareData);

		/// <summary>
		/// �X�V
		/// </summary>
		/// <returns> ��Ԃ̕ύX </returns>
		StateChange update(BoardShareData& shareData);

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="shareData"> ���L�f�[�^ </param>
		void draw(const BoardShareData& shareData) const;

		/// <summary>
		/// ���(����)�̎擾
		/// </summary>
		/// <returns> ���(����) </returns>
		Role getRole() const
		{
			return m_role;
		}

		/// <summary>
		/// �E�B���h�E�͈̔͂����������`�̎擾
		/// </summary>
		/// <returns> �E�B���h�E�͈̔͂����������` </returns>
		Rect getRect() const
		{
			return std::move(Rect(m_pos, m_size));
		}

		/// <summary>
		/// �}�E�X�ō��N���b�N������
		/// </summary>
		/// <returns></returns>
		bool mouseLeftDown() const
		{
			return MouseL.down() 
				&& Rect(m_pos, m_size).mouseOver() 
				&& (Cursor::PosF().y < Scene::Height() - BoardSymbol::height());
		}

		/// <summary>
		/// �\��
		/// </summary>
		void display()
		{
			m_state = StateChange::NONE;
		}

		/// <summary>
		/// �ŏ���
		/// </summary>
		void minimize()
		{
			m_state = StateChange::MINIMIZE;
		}

		/// <summary>
		/// �폜�҂���Ԃł̍X�V
		/// </summary>
		/// <returns> �폜����Ƃ� true, �����łȂ��Ƃ� false </returns>
		bool erasingUpdate()
		{
			return changeAlpha();
		}

	protected:


		/// <summary>
		/// �{�[�h���̓��͂̎�t
		/// </summary>
		/// <param name="shareData"> ���L�f�[�^ </param>
		virtual void inputInBoard(BoardShareData& shareData) = 0;

		/// <summary>
		/// �{�[�h���̍X�V
		/// </summary>
		/// <param name="shareData"> ���L�f�[�^ </param>
		/// <remarks>
		/// �}�E�X��L�[�{�[�h�̓��͂��K�v�Ȃ��̂�
		/// input�֐��ōs��
		/// </remarks>
		virtual void updateInBoard(BoardShareData& shareData) = 0;

		/// <summary>
		/// �{�[�h���̕`��
		/// </summary>
		/// <param name="shareData"> ���L�f�[�^ </param>
		virtual void drawInBoard(const BoardShareData& shareData) const = 0;

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
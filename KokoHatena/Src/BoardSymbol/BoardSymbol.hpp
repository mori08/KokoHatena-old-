#pragma once


#include <Siv3D.hpp>


namespace Kokoha
{
	/// <summary>
	/// BoardSymbol�N���X
	/// Board�̏�Ԃ��Ǘ�����
	/// </summary>
	class BoardSymbol
	{
	public:

		// Board�̏��
		enum class BoardState
		{
			NONE,    // �C���X�^���X�Ȃ�
			HIDE,    // ��\��
			DISPLAY, // �\����
			TOP      // ��ԑO��
		};

	public:

		// ��ӂ̒���
		static const int32 SIZE = 60;

	private:

		// �^�X�N�o�[�ɔz�u����ʒu
		const Rect m_region;

		// ���ʔԍ�
		const int32 m_id;

		// �Ή�����Board�̏��
		BoardState m_state;

		// ���̌���
		double m_lightWidth;

		// �s�N�Z���V�F�[�_
		const PixelShader m_shader;

	public:

		/// <summary>
		/// Board�̏�ԊǗ�
		/// </summary>
		/// <param name="pos"> ���W </param>
		/// <param name="id" > �ԍ� </param>
		BoardSymbol(const Point& pos, const int32& id);

	public:

		/// <summary>
		/// �X�V
		/// </summary>
		void update();

		/// <summary>
		/// �`��
		/// </summary>
		void draw() const;

		/// <summary>
		/// Board�̐ݒ�̕ύX
		/// </summary>
		/// <param name="state"> Board�̐ݒ� </param>
		void setState(BoardState state)
		{
			m_state = state;
		}

	private:

		/// <summary>
		/// ��ԂɑΉ�������̌����̎擾
		/// </summary>
		/// <returns> ��ԂɑΉ�������̌��� </returns>
		double getLightWidth() const;

	};
}
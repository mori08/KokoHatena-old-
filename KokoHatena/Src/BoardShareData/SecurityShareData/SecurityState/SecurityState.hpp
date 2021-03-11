#pragma once


#include <Siv3D.hpp>


namespace Kokoha
{
	/// <summary>
	/// SecurityState�N���X
	/// SecurityBoard�̏��
	/// </summary>
	class SecurityState
	{
	private:

		const std::function<void()> m_closeProcess;

	public:

		SecurityState()
			: m_closeProcess([](){})
		{}

		SecurityState(const std::function<void()>& closeProcess)
			: m_closeProcess(closeProcess)
		{}

		virtual ~SecurityState() {};

		/// <summary>
		/// �{�[�h������Ƃ��̏���
		/// </summary>
		void closeProcess() const
		{
			m_closeProcess();
		}

		/// <summary>
		/// �{�[�h�̓��͏���
		/// </summary>
		/// <param name="mouseLeftUp"> �}�E�X�̍��N���b�N���̍��W </param> 
		virtual void input(Optional<Vec2> mouseUpPoint) = 0;

		/// <summary>
		/// �{�[�h�̍X�V����
		/// </summary>
		/// <param name="mousePosInBoard"> �{�[�h�̓��ł̃}�E�X���W </param>
		virtual void update(const Vec2& cursorPosInBoard) = 0;

		/// <summary>
		/// �{�[�h�̕`�揈��
		/// </summary>
		virtual void draw()const = 0;

	};
}
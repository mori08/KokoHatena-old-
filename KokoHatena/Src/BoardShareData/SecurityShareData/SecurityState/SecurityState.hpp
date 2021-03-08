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
	public:

		virtual ~SecurityState() {};

		/// <summary>
		/// �{�[�h������Ƃ��̏���
		/// </summary>
		virtual void closeProcess() {};

		/// <summary>
		/// �{�[�h�̓��͏���
		/// </summary>
		/// <param name="mouseLeftUp"> �}�E�X�̍��N���b�N���̍��W </param> 
		virtual void input(Optional<Vec2> mouseUpPoint) = 0;

		/// <summary>
		/// �{�[�h�̍X�V����
		/// </summary>
		virtual void update() = 0;

		/// <summary>
		/// �{�[�h�̕`�揈��
		/// </summary>
		virtual void draw()const = 0;

	};
}
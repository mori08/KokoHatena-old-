#pragma once


#include <Siv3D.hpp>


namespace Kokoha
{
	/// <summary>
	/// AccessPlayer�̐i�ތ�����\��
	/// </summary>
	class PlayerDirection
	{
	private:

		// �\��������W
		Vec2 m_pos;

		// �ړI�n
		Vec2 m_goal;

		// �F�̕s�����x
		double m_alpha;

		// �ړI�n��ύX����
		bool m_isChangingGoal;

	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="playerPos"> �v���C���[�̍��W </param>
		/// <param name="goalPos"> �ړI�n�̍��W </param>
		/// <param name="isChangingGoal"> �S�[����ύX���� </param>
		void input(const Vec2& playerPos, const Vec2& goalrPos, bool isChangingGoal);

		/// <summary>
		/// �X�V
		/// </summary>
		void update();

		/// <summary>
		/// �`��
		/// </summary>
		void draw() const;

	};
}
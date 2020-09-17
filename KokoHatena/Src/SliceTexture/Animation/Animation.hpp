#pragma once

#include <Siv3D.hpp>


namespace Kokoha
{
	// �摜�̐؂�ւ���              ����    ���W
	using PosOrder = Array<std::pair<double, Point>>;

	/// <summary>
	/// Animation�N���X
	/// �摜�̐؂�ւ����Ƃ���ɂ����鎞�Ԃ��܂Ƃ߂�����
	/// </summary>
	class Animation
	{
	private:

		// �摜��؂�ւ��I���܂łɂ����鎞��
		const double m_totalSecond;

		// �摜�̐؂�ւ���
		const PosOrder m_posOrder;

		// true ���[�v���� , false �Ō�̍��W�Œ�~
		const bool m_isLoop;

	public:

		/// <summary>
		/// �摜�̐؂�ւ����Ƃ���ɂ����鎞�ԂȂ�
		/// </summary>
		/// <param name="posList"> �摜�̐؂�ւ��� </param>
		/// <param name="posList"> ���[�v           </param>
		Animation(const PosOrder& posOrder, bool isLoop);

		/// <summary>
		/// �摜�̍��W���擾
		/// </summary>
		/// <param name="animSecond"> ���� </param>
		/// <returns> ���ԂɑΉ������摜�ԍ� </returns>
		/// <remarks>
		/// O(log|m_posOrder�̃T�C�Y|)���ԕK�v
		/// �ΐ����ԂȂ̂ő債�����Ԃ�v���Ȃ���
		/// �ꉞ�CO(1)�łȂ����Ƃɒ���
		/// </remarks>
		Point getTexturePos(double animSecond) const;

		/// <summary>
		/// �摜��؂�ւ��I���܂łɂ����鎞�Ԃ̎擾
		/// </summary>
		/// <returns> �摜��؂�ւ��I���܂łɂ����鎞�� </returns>
		double getTotalSecond() const
		{
			return m_totalSecond;
		}

		/// <summary>
		/// ���[�v���邩����
		/// </summary>
		/// <returns> ���[�v����Ƃ� true , �����łȂ��Ƃ� false </returns>
		bool loop() const
		{
			return m_isLoop;
		}

	private:

		/// <summary>
		/// m_totalSecond�̌v�Z
		/// </summary>
		static double getTotalSecond(const PosOrder& posOrder);

		/// <summary>
		/// m_posOrder�̎��Ԃ�݌v�ɕύX
		/// </summary>
		static PosOrder getPosOrder(PosOrder posOrder);

	};
}
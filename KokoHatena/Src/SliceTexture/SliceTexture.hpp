#pragma once


#include "Animation/Animation.hpp"


namespace Kokoha
{
	/// <summary>
	/// SliceTexture�N���X
	/// 1���̉摜�𕡐��̉摜�ɕ���,
	/// �؂�ւ��Ȃǂ��s����悤�ɂ���.
	/// </summary>
	class SliceTexture
	{
	private:

		// �摜�̖��O
		const String m_textureName;

		// �摜��؂蕪����傫��
		const Size m_sliceSize;

		// true �̂Ƃ����E���]���ĕ`��
		bool m_mirror;

		// (1��)�A�j���[�V���������s���Ă��鎞��
		double m_animSecond;

		// ���݂�Animation�̖��O
		String m_animName;

		// Animation���Ǘ�����}�b�v
		std::unordered_map<String, Animation> m_animMap;

	public:

		/// <summary>
		/// �摜�̐؂蕪��
		/// </summary>
		/// <param name="textureName"> �摜�̖��O             </param>
		/// <param name="sliceSize">   �摜��؂蕪����傫�� </param>
		/// <param name="pos">         �摜�̏����ԍ�         </param>
		SliceTexture(const String& textureName, const Size& sliceSize);

		/// <summary>
		/// �A�j���[�V�����̐ݒ�
		/// </summary>
		/// <param name="anim"> �A�j���[�V���� </param>
		void setAnimation(const String& name, const Animation& anim)
		{
			m_animMap.try_emplace(name, anim);
		}

		/// <summary>
		/// �摜�̕ύX
		/// </summary>
		/// <returns>
		/// �摜�̐؂�ւ����I�������Ƃ� true , �����łȂ��Ƃ� false
		/// ���[�v���Ă���Ƃ��� true ����ɕԂ��̂Œ���
		/// </returns>
		bool update();

		/// <summary>
		/// ���ݎ��s���̃A�j���[�V�������I�����Ă��邩����
		/// </summary>
		/// <returns> �I�����Ă���Ȃ� true , ���s���Ȃ� false </returns>
		bool isFinished() const
		{
			return m_animSecond > m_animMap.find(m_animName)->second.getTotalSecond();
		}

		/// <summary>
		/// �摜�̔��]
		/// </summary>
		void mirror()
		{
			m_mirror = !m_mirror;
		}

		/// <summary>
		/// �A�j���[�V�����̊J�n
		/// </summary>
		/// <param name="name"> �A�j���[�V�����̖��O </param>
		void start(const String name);

		/// <summary>
		/// �ʃA�j���[�V�����̊J�n
		/// ���ݎ��s���̂��̂Ɠ������O���w�肳�ꂽ�牽�����Ȃ�
		/// </summary>
		/// <param name="name"> �A�j���[�V������ </param>
		void startAnotherAnimation(const String name);

		/// <summary>
		/// �摜�̕ύX
		/// </summary>
		TextureRegion getTexture() const;

		/// <summary>
		/// �摜��؂蕪����傫���̎擾
		/// </summary>
		const Size& getSliceSize() const
		{
			return m_sliceSize;
		}

	};
}
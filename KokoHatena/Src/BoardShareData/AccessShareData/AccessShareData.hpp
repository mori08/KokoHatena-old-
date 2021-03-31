#pragma once


#include "StageData/StageData.hpp"
#include "Light/AccessLight.hpp"


namespace Kokoha
{
	/// <summary>
	/// AccessShareData�N���X
	/// �A�N�Z�X(�p�Y���A�N�V����)�p�Ɏg�����L�f�[�^
	/// </summary>
	class AccessShareData
	{
	private:

		// �n�`�E�o�H�̃f�[�^
		StageData m_stageData;

		// �����_�[�e�N�X�`��
		const MSRenderTexture m_render;

		// ���̃��X�g
		std::list<AccessLight> m_lightList;

	public:

		AccessShareData();

	public:

		/// <summary>
		/// ������
		/// </summary>
		void init();

		/// <summary>
		/// �X�e�[�W�f�[�^���L�q�����t�@�C���̓ǂݍ���
		/// </summary>
		/// <returns> �G���[���b�Z�[�W </returns>
		Optional<String> load();

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
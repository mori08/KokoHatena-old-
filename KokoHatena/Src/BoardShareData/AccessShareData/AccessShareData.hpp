#pragma once


#include "StageData/StageData.hpp"
#include "Light/AccessLight.hpp"
#include "Object/AccessObject.hpp"


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

		// �I�u�W�F�N�g�̃��X�g
		std::list<AccessObjectPtr> m_objectList;

		// �I�u�W�F�N�g�𐶐�����֐��̃}�b�v
		std::unordered_map<String, std::function<AccessObjectPtr(const Vec2&)>> m_makeObjectFuncMap;

		// ���̃��X�g
		std::list<AccessLight> m_lightList;

	public:

		AccessShareData();

	public:

		/* AccessBoard�Ŏg�p */

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
		/// �J�[�\���̍��W�̎擾
		/// </summary>
		/// <param name="cursorPos"> �J�[�\���̍��W </param>
		void input(const Vec2& cursorPos);

		/// <summary>
		/// �X�V
		/// </summary>
		void update();

		/// <summary>
		/// �`��
		/// </summary>
		void draw() const;

	public:

		/* AccessObject�Ŏg�p */

		/// <summary>
		/// StageData�̎擾
		/// </summary>
		/// <returns> StageData </returns>
		const StageData& getStageData()const
		{
			return m_stageData;
		}

		/// <summary>
		/// ���̒ǉ�
		/// </summary>
		/// <param name="circle"> ���͈̔�(���S�Ɣ��a) </param>
		/// <param name="direction"> ���� </param>
		/// <param name="angle"> �͈� </param>
		void addLight(const Circle& circle, double direction = 0, double angle = Math::Pi)
		{
			m_lightList.emplace_back(circle, direction, angle);
		}

	private:

		/// <summary>
		/// �I�u�W�F�N�g���쐬����֐��̓o�^
		/// </summary>
		/// <typeparam name="ObjectType"> �I�u�W�F�N�g�̌^ </typeparam>
		/// <param name="name"> �I�u�W�F�N�g�̖��O </param>
		template<typename ObjectType>
		void setMakeObjectFunc(const String& name)
		{
			m_makeObjectFuncMap[name] = [](const Vec2& pos) { return std::make_unique<ObjectType>(pos); };
		}

	};
}
#pragma once


#include "Type/AccessObjectType.hpp"


namespace Kokoha
{
	class AccessShareData;

	/// <summary>
	/// AccessObject�N���X
	/// AccessShareData�Ŏg�p����I�u�W�F�N�g
	/// </summary>
	class AccessObject
	{
	protected:

		// �ʒu�Ɣ���p�͈̔�
		Circle m_body;

		// ���
		const AccessObjectType m_type;

	public:

		AccessObject(const Circle& body, const AccessObjectType& type)
			: m_body(body)
			, m_type(type)
		{
		}

		virtual ~AccessObject() {}

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="cursorPos"> �J�[�\���̍��W </param>
		virtual void input(const Vec2&) {}

		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="shareData"> ���L�f�[�^ </param>
		virtual void update(AccessShareData& shareData) = 0;

		/// <summary>
		/// �`��
		/// </summary>
		virtual void draw()const = 0;

		/// <summary>
		/// �폜����
		/// </summary>
		/// <returns> true�̂Ƃ��폜 </returns>
		virtual bool isEraseAble()const
		{
			return false;
		}

		/// <summary>
		/// ���I�u�W�F�N�g�̎�ނƈʒu�̊m�F
		/// </summary>
		/// <param name="another"> ���I�u�W�F�N�g </param>
		virtual void checkAnother(const AccessObject& another) = 0;

	public:

		/// <summary>
		/// �w��̎�ނ̃I�u�W�F�N�g�ƏՓ˂̊m�F
		/// </summary>
		/// <param name="anther"> ���̃I�u�W�F�N�g </param>
		/// <param name="type"  > �w�肷����     </param>
		/// <returns>
		/// another���w��̎�ނ̃I�u�W�F�N�g���Փ˂��Ă���Ƃ� true , �����łȂ��Ƃ� false
		/// </returns>
		bool checkTypeAndCollision(const AccessObject& another, const AccessObjectType& type) const
		{
			return (another.m_type & type) && m_body.intersects(another.m_body);
		}

		/// <summary>
		/// �w��̎�ނ̃I�u�W�F�N�g�̂Ƃ����W�̎擾
		/// </summary>
		/// <param name="type"> �w�肷���� </param>
		/// <returns> ���W </returns>
		Optional<Vec2> checkTypeAndGetPos(const AccessObjectType& type) const
		{
			return (m_type & type) ? Optional<Vec2>(m_body.center) : Optional<Vec2>(none);
		}

	};

	using AccessObjectPtr = std::unique_ptr<AccessObject>;
}
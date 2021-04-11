#pragma once


#include <Siv3D.hpp>


namespace Kokoha
{
	/// <summary>
	/// AccessObjectType�N���X
	/// AccessObject�̎�� �܂��͂��̏W��
	/// unit8�^��1bit��1��ނɊ��蓖�Ă�
	/// </summary>
	class AccessObjectType
	{
	private:

		uint8 m_value;

	public:

		static const AccessObjectType PLAYER;

	private:

		constexpr AccessObjectType(uint8 value)
			: m_value(value)
		{
		}

	public:

		/// <summary>
		/// �a�W���̍쐬
		/// </summary>
		AccessObjectType operator|(const AccessObjectType& another)const
		{
			return AccessObjectType(m_value | another.m_value);
		}

		/// <summary>
		/// �ϏW���̍쐬
		/// </summary>
		AccessObjectType operator&(const AccessObjectType& another)const
		{
			return AccessObjectType(m_value & another.m_value);
		}

		/// <summary>
		/// ���W���̍쐬
		/// </summary>
		AccessObjectType operator-(const AccessObjectType& another)const
		{
			return AccessObjectType(m_value & ~another.m_value);
		}

		/// <summary>
		/// �W���ɒǉ�
		/// </summary>
		const AccessObjectType& operator|=(const AccessObjectType& another)
		{
			m_value |= another.m_value;
			return *this;
		}

		/// <summary>
		/// �W������폜
		/// </summary>
		const AccessObjectType& operator-=(const AccessObjectType& another)
		{
			m_value &= ~another.m_value;
			return *this;
		}

		/// <summary>
		/// ��W���̎擾
		/// </summary>
		const AccessObjectType operator~()const
		{
			return AccessObjectType(~m_value);
		}

		/// <summary>
		/// ��W���̂Ƃ� false , �����łȂ��Ƃ� true
		/// </summary>
		explicit operator bool() const
		{
			return m_value != 0;
		}

	};
}
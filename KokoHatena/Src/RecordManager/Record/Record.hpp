#pragma once


#include<Siv3D.hpp>


namespace Kokoha
{
	/// <summary>
	/// Record�N���X
	/// �t���O�␔�l�C������̊Ǘ�
	/// ��bit�ɑΉ����邩�w��
	/// </summary>
	class Record
	{
	private:

		// ����
		const int32 m_digit;

		// �ő�l
		const int32 m_maxValue;

		// �����l
		const int32 m_defaultValue;

		// �l
		uint32 m_value;

		// �����̍��v�l
		static int32 s_digitTotal;

	public:

		/// <summary>
		/// ���R�[�h���\������v�f
		/// </summary>
		/// <param name="digit">        ����   </param>
		/// <param name="defaultValue"> �����l </param>
		Record(int32 digit, int32 defaultValue);

		/// <summary>
		/// ������
		/// </summary>
		void init()
		{
			m_value = m_defaultValue;
		}

		/// <summary>
		/// �l�̐ݒ�
		/// </summary>
		/// <param name="value"> �ύX�������l </param>
		void set(int32 value)
		{
			m_value = Clamp(value, 0, m_maxValue);
		}

		/// <summary>
		/// �l�̎擾
		/// </summary>
		/// <returns>
		/// �Ǘ����Ă���l
		/// </returns>
		int32 get() const
		{
			return m_value;
		}

		/// <summary>
		/// �Í����p�̃��X�g�ɂ��̃��R�[�h��ǉ�
		/// </summary>
		/// <param name="dataList"> �Í����p�̃��X�g </param>
		void addRecordToEncryptionList(std::list<int32>& dataList) const;

		/// <summary>
		/// �����p�̃��X�g����l��ݒ�
		/// </summary>
		/// <param name="dataList"> �������p�̃��X�g </param>
		void setValueFromDecryption(std::list<int32>& dataList);

		/// <summary>
		/// �����̍��v�l�̎擾
		/// </summary>
		/// <returns>
		/// �����̍��v�l
		/// </returns>
		static int32 getDigitTotal()
		{
			return s_digitTotal;
		}

	};
}
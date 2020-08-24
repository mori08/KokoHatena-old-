#pragma once


#include"Record/Record.hpp"


namespace Kokoha
{
	/// <summary>
	/// RecordManager�N���X
	/// ���R�[�h (�Z�[�u�f�[�^) �̃��[�h��Z�[�u,
	/// �t���O�␔�l�̕ύX,�擾���s���܂�.
	/// </summary>
	class RecordManager
	{
	public:

		enum class LoadResult
		{
			NEW_GAME, // RECORD.txt�����݂��Ȃ��Ƃ�
			CONTINUE, // RECORD.txt�𐳂����ǂݍ��߂��Ƃ�
			ERROR     // RECORD.txt�𐳂����ǂݍ��߂Ȃ��Ƃ�
		};

	private:

		// ���R�[�h�̃}�b�v
		std::map<String, Record> m_recordMap;

	private:

		RecordManager();

		RecordManager(const RecordManager&)            = default;
		RecordManager& operator=(const RecordManager&) = default;
		RecordManager(RecordManager&&)                 = default;
		RecordManager& operator=(RecordManager&&)      = default;

	public:

		/// <summary>
		/// �V���O���g���Ƃ��ĊǗ����Ă���RecordManager�̃C���X�^���X�̎擾
		/// </summary>
		/// <returns>
		/// �C���X�^���X
		/// </summary>
		static RecordManager& instance()
		{
			static RecordManager recordManager;
			return recordManager;
		}

		/// <summary>
		/// �Z�[�u�f�[�^�p�t�@�C�����烍�[�h
		/// </summary>
		LoadResult load();

		/// <summary>
		/// �S���R�[�h�̏�����
		/// </summary>
		void initAllRecord();

		/// <summary>
		/// �Z�[�u�f�[�^�p�t�@�C���ɃZ�[�u
		/// </summary>
		void save();

		/// <summary>
		/// ���R�[�h�̐ݒ�
		/// </summary>
		/// <param name="name" > ���O         </param>
		/// <param name="value"> �ύX�������l </param>
		void setRecord(const String& name, int32 value);

		/// <summary>
		/// ���R�[�h�̎擾
		/// </summary>
		/// <param name="name"> ���O </param>
		/// <returns> ���R�[�h�̒l </returns>
		int32 getRecord(const String& name) const;

	private:

		/// <summary>
		/// ���R�[�h�̈Í���
		/// </summary>
		/// <returns>
		/// �Í���������̕�����
		/// </returns>
		String encryption() const;

		/// <summary>
		/// �Í����𕜍�, �t���O�̃��X�g�Ɋi�[
		/// </summary>
		/// <param name="str"> �Í��� </param>
		/// <returns> �����ɐ��������Ƃ� true , �����łȂ��Ƃ� false </returns>
		bool decryption(const String& str);

	};
}
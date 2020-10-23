#pragma once


#include<Siv3D.hpp>


namespace Kokoha
{
	/// <summary>
	/// MyPixelShader�N���X
	/// �����ō쐬�����s�N�Z���V�F�[�_�̊Ǘ�
	/// </summary>
	class MyPixelShader
	{
	public:

		/// <summary>
		/// ���
		/// </summary>
		enum class Type
		{
			BOARD_SYMBOL,
			TITLE_LOGO
		};

	private:

		// �����ō쐬�����s�N�Z���V�F�[�_�̃}�b�v
		std::unordered_map<Type, const PixelShader> m_shaderMap;

	private:

		MyPixelShader() = default;

		/// <summary>
		/// �N���X���Ŏg�p����C���X�^���X�̎擾
		/// </summary>
		/// <returns> �C���X�^���X </returns>
		static MyPixelShader& instance()
		{
			static MyPixelShader myShader;
			return myShader;
		}

	public:

		/// <summary>
		/// �s�N�Z���V�F�[�_�̓ǂݍ���
		/// </summary>
		static void loadPixelShader();

		/// <summary>
		/// �s�N�Z���V�F�[�_�̎擾
		/// </summary>
		/// <returns> �擾 </returns>
		static const PixelShader& get(Type type);

	};
}
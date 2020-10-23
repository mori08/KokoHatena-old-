#pragma once


#include<Siv3D.hpp>


namespace Kokoha
{
	/// <summary>
	/// MyPixelShaderクラス
	/// 自分で作成したピクセルシェーダの管理
	/// </summary>
	class MyPixelShader
	{
	public:

		/// <summary>
		/// 種類
		/// </summary>
		enum class Type
		{
			BOARD_SYMBOL,
			TITLE_LOGO
		};

	private:

		// 自分で作成したピクセルシェーダのマップ
		std::unordered_map<Type, const PixelShader> m_shaderMap;

	private:

		MyPixelShader() = default;

		/// <summary>
		/// クラス内で使用するインスタンスの取得
		/// </summary>
		/// <returns> インスタンス </returns>
		static MyPixelShader& instance()
		{
			static MyPixelShader myShader;
			return myShader;
		}

	public:

		/// <summary>
		/// ピクセルシェーダの読み込み
		/// </summary>
		static void loadPixelShader();

		/// <summary>
		/// ピクセルシェーダの取得
		/// </summary>
		/// <returns> 取得 </returns>
		static const PixelShader& get(Type type);

	};
}
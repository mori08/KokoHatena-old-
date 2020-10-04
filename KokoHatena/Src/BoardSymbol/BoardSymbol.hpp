#pragma once


#include <Siv3D.hpp>


namespace Kokoha
{
	/// <summary>
	/// BoardSymbolクラス
	/// Boardの状態を管理する
	/// </summary>
	class BoardSymbol
	{
	public:

		// Boardの状態
		enum class BoardState
		{
			NONE,    // インスタンスなし
			HIDE,    // 非表示
			DISPLAY, // 表示中
			TOP      // 一番前面
		};

	public:

		// 一辺の長さ
		static const int32 SIZE = 60;

	private:

		// タスクバーに配置する位置
		const Rect m_region;

		// 識別番号
		const int32 m_id;

		// 対応するBoardの状態
		BoardState m_state;

		// 光の厚さ
		double m_lightWidth;

		// ピクセルシェーダ
		const PixelShader m_shader;

	public:

		/// <summary>
		/// Boardの状態管理
		/// </summary>
		/// <param name="pos"> 座標 </param>
		/// <param name="id" > 番号 </param>
		BoardSymbol(const Point& pos, const int32& id);

	public:

		/// <summary>
		/// 更新
		/// </summary>
		void update();

		/// <summary>
		/// 描画
		/// </summary>
		void draw() const;

		/// <summary>
		/// Boardの設定の変更
		/// </summary>
		/// <param name="state"> Boardの設定 </param>
		void setState(BoardState state)
		{
			m_state = state;
		}

	private:

		/// <summary>
		/// 状態に対応する光の厚さの取得
		/// </summary>
		/// <returns> 状態に対応する光の厚さ </returns>
		double getLightWidth() const;

	};
}
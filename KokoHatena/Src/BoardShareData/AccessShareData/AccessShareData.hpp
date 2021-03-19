#pragma once


#include "StageData/StageData.hpp"


namespace Kokoha
{
	/// <summary>
	/// AccessShareDataクラス
	/// アクセス(パズルアクション)用に使う共有データ
	/// </summary>
	class AccessShareData
	{
	private:

		// 地形・経路のデータ
		StageData m_stageData;

		// レンダーテクスチャ
		const MSRenderTexture m_render;

	public:

		AccessShareData();

	public:

		/// <summary>
		/// ステージデータを記述したファイルの読み込み
		/// </summary>
		/// <returns> エラーメッセージ </returns>
		Optional<String> load();

		/// <summary>
		/// 更新
		/// </summary>
		void update();

		/// <summary>
		/// 描画
		/// </summary>
		void draw() const;

	};
}
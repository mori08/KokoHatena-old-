#pragma once


#include "StageData/StageData.hpp"
#include "Light/AccessLight.hpp"


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

		// 光のリスト
		std::list<AccessLight> m_lightList;

	public:

		AccessShareData();

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		void init();

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
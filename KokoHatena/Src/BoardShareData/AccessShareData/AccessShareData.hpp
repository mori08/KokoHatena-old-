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

		/// <summary>
		/// 光を描画する
		/// </summary>
		/// <param name="circle"> 光 </param>
		/// <param name="direction"> 向き </param>
		/// <param name="cosin"> 視野[-1,1] -1以下なら全範囲, 1以上なら光なし </param>
		void drawLight(const Circle& circle,Vec2& direction,double cosin) const;

	};
}
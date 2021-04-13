#pragma once


#include "StageData/StageData.hpp"
#include "Light/AccessLight.hpp"
#include "Object/AccessObject.hpp"


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

		// オブジェクトのリスト
		std::list<AccessObjectPtr> m_objectList;

		// オブジェクトを生成する関数のマップ
		std::unordered_map<String, std::function<AccessObjectPtr(const Vec2&)>> m_makeObjectFuncMap;

		// 光のリスト
		std::list<AccessLight> m_lightList;

	public:

		AccessShareData();

	public:

		/* AccessBoardで使用 */

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
		/// カーソルの座標の取得
		/// </summary>
		/// <param name="cursorPos"> カーソルの座標 </param>
		void input(const Vec2& cursorPos);

		/// <summary>
		/// 更新
		/// </summary>
		void update();

		/// <summary>
		/// 描画
		/// </summary>
		void draw() const;

	public:

		/* AccessObjectで使用 */

		/// <summary>
		/// StageDataの取得
		/// </summary>
		/// <returns> StageData </returns>
		const StageData& getStageData()const
		{
			return m_stageData;
		}

		/// <summary>
		/// 光の追加
		/// </summary>
		/// <param name="circle"> 光の範囲(中心と半径) </param>
		/// <param name="direction"> 方向 </param>
		/// <param name="angle"> 範囲 </param>
		void addLight(const Circle& circle, double direction = 0, double angle = Math::Pi)
		{
			m_lightList.emplace_back(circle, direction, angle);
		}

	private:

		/// <summary>
		/// オブジェクトを作成する関数の登録
		/// </summary>
		/// <typeparam name="ObjectType"> オブジェクトの型 </typeparam>
		/// <param name="name"> オブジェクトの名前 </param>
		template<typename ObjectType>
		void setMakeObjectFunc(const String& name)
		{
			m_makeObjectFuncMap[name] = [](const Vec2& pos) { return std::make_unique<ObjectType>(pos); };
		}

	};
}
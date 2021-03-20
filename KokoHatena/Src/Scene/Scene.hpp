#pragma once


#include "../BoardShareData/BoardShareData.hpp"


// シーンの名前
enum class SceneName
{
	TITLE,       // タイトル

	TEST_LOAD,   // ロードシーンのテスト
	RECORD_LOAD, // レコードのロード
	DESKTOP_LOAD, // デスクトップのロード

	DESKTOP      // デスクトップ
};

// シーンで共有されるデータ
struct ShareData
{
	// Board間の共有データ
	Kokoha::BoardShareData boardShareData;
};

// シーン管理クラス
using MyApp = SceneManager<SceneName, ShareData>;
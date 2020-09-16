#pragma once


#include<Siv3D.hpp>


// シーンの名前
enum class SceneName
{
	TITLE,      // タイトル

	TEST_LOAD,  // ロードシーンのテスト
	RECORD_LOAD // レコードのロード
};

// シーンで共有されるデータ
struct ShareData
{

};

// シーン管理クラス
using MyApp = SceneManager<SceneName, ShareData>;
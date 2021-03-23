
#include"MyLibrary/MyLibrary.hpp"
#include"Config/Config.hpp"
#include"MyPixelShader/MyPixelShader.hpp"
#include"RecordManager/RecordManager.hpp"

// シーン
#include "Scene/Title/TitleScene.hpp"
#include "Scene/Load/TestLoad/TestLoadScene.hpp"
#include "Scene/Load/Record/LoadRecordScene.hpp"
#include "Scene/Load/Desktop/LoadDesktopScene.hpp"
#include "Scene/Desktop/DesktopScene.hpp"


void Main()
{
	// ウィンドウの設定
	Window::Resize(Kokoha::Config::get<Point>(U"Window.size"));
	Window::SetTitle(Kokoha::Config::get<String>(U"Window.name"));

	// 描画設定
	Scene::SetBackground(Kokoha::MyBlack);
	Scene::Resize(Kokoha::Config::get<Point>(U"Window.size"));

	// アセット管理
	Kokoha::registerAsset(U"asset/");
	Kokoha::MyPixelShader::loadPixelShader();
	for (int32 i = 10; i <= 40; ++i)
	{
		FontAsset::Register(ToString(i), i, Typeface::Medium);
	}

	// シーン
	MyApp sceneManager;
	sceneManager.add<Kokoha::TitleScene>      (SceneName::TITLE);
	sceneManager.add<Kokoha::TestLoadScene>   (SceneName::TEST_LOAD);
	sceneManager.add<Kokoha::LoadRecordScene> (SceneName::RECORD_LOAD);
	sceneManager.add<Kokoha::LoadDesktopScene>(SceneName::DESKTOP_LOAD);
	sceneManager.add<Kokoha::DesktopScene>    (SceneName::DESKTOP);

	while (System::Update())
	{
		sceneManager.update();

		//Kokoha::showFPS();
		Kokoha::RecordManager::instance().writeDebugText();
	}
}

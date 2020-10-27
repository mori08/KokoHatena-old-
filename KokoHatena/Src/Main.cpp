
#include"MyLibrary/MyLibrary.hpp"
#include"Config/Config.hpp"
#include"MyPixelShader/MyPixelShader.hpp"

// シーン
#include "Scene/Title/TitleScene.hpp"
#include "Scene/Load/TestLoad/TestLoadScene.hpp"
#include "Scene/Load/Record/LoadRecordScene.hpp"
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
	FontAsset::Register(U"10", 10, Typeface::Medium);
	FontAsset::Register(U"15", 15, Typeface::Medium);
	FontAsset::Register(U"20", 20, Typeface::Medium);
	FontAsset::Register(U"30", 30, Typeface::Medium);
	FontAsset::Register(U"40", 40, Typeface::Medium);

	// シーン
	MyApp sceneManager;
	sceneManager.add<Kokoha::TitleScene>     (SceneName::TITLE);
	sceneManager.add<Kokoha::TestLoadScene>  (SceneName::TEST_LOAD);
	sceneManager.add<Kokoha::LoadRecordScene>(SceneName::RECORD_LOAD);
	sceneManager.add<Kokoha::DesktopScene>   (SceneName::DESKTOP);

	while (System::Update())
	{
		sceneManager.update();

		Kokoha::showFPS();
	}
}
